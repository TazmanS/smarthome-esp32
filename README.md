# SmartHome ESP32 🔧

Lightweight ESP32 firmware for a small smart-home temperature monitoring demo.

- Reads temperature from an LM35 sensor (ADC)
- Displays readings on an LCD1602
- Sends temperature via MQTT
- Uses FreeRTOS tasks for modular responsibilities

---

## Quick facts ✅

- MCU: ESP32
- Language: C (CMake / PlatformIO compatible)
- Docs: Doxygen output in `docs/doxygen/html`

---

## Requirements ⚙️

Choose one of the supported build workflows:

- PlatformIO (recommended): install PlatformIO Core (CLI) or use the VS Code PlatformIO extension
- ESP-IDF / CMake: install the ESP-IDF toolchain and set up `idf.py`

Also: Python 3, Git, and a serial terminal program (or `pio device monitor` / `idf.py monitor`).

---

## Setup & Configuration 💡

1. Configure secrets:
   - Copy `src/secrets/secrets.example.c` → `src/secrets/secrets.c` and fill in your WiFi and MQTT credentials.
   - `src/secrets/secrets.h` declares the secrets used across the project.

2. Hardware wiring (high level):
   - LM35 → ADC input
   - LCD1602 → I2C / GPIO (see `src/sensors/lcd1602`)

---

## Build & Flash 🚀

PlatformIO (example):

```bash
# build
pio run
# build + upload (adjust environment if multiple boards defined)
pio run -t upload
# monitor serial
pio device monitor
```

ESP-IDF / CMake (example):

```bash
# inside project root (with ESP-IDF env loaded)
idf.py build
idf.py -p <PORT> flash monitor
```

---

## Documentation 📚

Doxygen documentation is generated to `docs/doxygen/html`. Open `docs/doxygen/html/index.html` in a browser to browse the code docs.

System diagrams:

- Architecture diagrams: `docs/ARCHITECTURE.md`
- Compact block diagram: `docs/BLOCK_DIAGRAM.md`

---

## Project structure 🔍

- `src/` — application source
  - `modules/` — platform modules (ADC, WiFi, MQTT, I2C)
  - `sensors/` — sensor drivers (LM35, LCD1602)
  - `tasks/` — FreeRTOS tasks (display, log, mqtt, send_temp)
  - `secrets/` — credentials (`secrets.example.c`)
- `docs/` — generated docs
- `platformio.ini`, `CMakeLists.txt`, `sdkconfig.*` — build configs

---

## Testing & Troubleshooting 🩺

- **Serial logs**: Check `pio device monitor` or terminal for runtime debug output
- **WiFi/MQTT**: Ensure credentials in `src/secrets/secrets.c` are correct and broker is reachable
- **Task WDT timeout**: All FreeRTOS tasks must call `esp_task_wdt_reset()` within timeout window (5s default, except IR task uses 4s timeout to handle extended idle periods)
- **Sensor data corruption**: Fixed buffer overflow - `sensor_data_t.key` now holds 32 bytes (was 16, causing truncation of `sensor/temperature` topic)
- **Build warnings**: Legacy ADC driver deprecation warning is normal; modern ADC API integration planned for future
- **Temperature readings**: Logged every 1 second from `SendTempTask`; check `critical(max)=...us` timing in logs
- **CPU load**: `CpuMonTask` logs CPU statistics every 5 seconds when FreeRTOS runtime stats enabled

---

## Contributing ✨

- Fork, create a branch, and open a pull request. Keep changes small and focused.

---

## License

No license file is included. Add a `LICENSE` if you want to specify one.

---

If you'd like, I can add a CI workflow (build/test) or a short guide for specific boards. 🔧