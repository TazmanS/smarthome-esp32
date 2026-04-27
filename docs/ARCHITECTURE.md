# SmartHome ESP32 - System Architecture

For a compact review-ready diagram, see `docs/BLOCK_DIAGRAM.md`.

## 1. System Initialization

Sequence diagram showing the initialization of all components at startup:

```mermaid
graph TB
    Start([app_main]) --> NVS[NVS Init<br/>Non-Volatile Storage]
    NVS --> Modules[Modules Init]
    Modules --> ADC[ADC Module]
    Modules --> WiFi[WiFi Module]
    Modules --> MQTT[MQTT Module]
    Modules --> I2C[I2C Module]
    Modules --> PWM[PWM Module]
    Modules --> RMT[RMT Module]
    
    Modules --> Sensors[Sensors Init]
    Sensors --> LM35[LM35<br/>Temperature Sensor]
    Sensors --> LCD[LCD1602<br/>Display]
    Sensors --> LEDs[LEDs]
    Sensors --> IR[IR Receiver]
    Sensors --> Photo[Photocell]
    Sensors --> PIR[PIR Motion]
    Sensors --> Motor[Motor]
    Sensors --> Servo[Servo]
    
    Sensors --> Interrupts[Interrupts Init]
    Interrupts --> Tasks[Tasks Init]
    
    Tasks --> ReadTemp[Send Temp Task]
    Tasks --> SendPhoto[Send Photocell Task]
    Tasks --> DisplayTask[Display Task]
    Tasks --> MQTTTask[MQTT Task]
    Tasks --> LogTask[Log Task]
    Tasks --> IRTask[IR Task]
    
    ReadTemp -->|temp_store_queue| MQTTQ["Queue System"]
    SendPhoto -->|photo_cell_store_queue| MQTTQ
    DisplayTask -->|display_queue| MQTTQ
    MQTTTask -->|mqtt_queue| MQTTQ
    LogTask -->|log_queue| MQTTQ
    IRTask -->|ir_queue| MQTTQ
    
    LM35 -->|ADC| ReadTemp
    Photo -->|ADC| SendPhoto
    LCD -->|I2C| DisplayTask
    IR -->|Signal| IRTask
    PIL[Broker] -.->|TCP/MQTT| MQTT
    
    MQTTQ -->|WiFi| Broker[(MQTT Broker)]
    MQTTQ -->|GPIO/I2C| LEDs
    MQTTQ -->|PWM| Motor
    MQTTQ -->|RMT| Servo
    
    style Start fill:#90EE90
    style Broker fill:#FFB6C6
    style MQTTQ fill:#87CEEB
    style Tasks fill:#DDA0DD
    style Modules fill:#F0E68C
```

## 2. Data Flow

Diagram showing data movement between sensors, tasks, queues, and cloud:

```mermaid
graph TB
    subgraph Hardware["🔌 HARDWARE"]
        LM35["LM35 Sensor<br/>(Temperature)"]
        Photo["Photocell<br/>(Light Level)"]
        PIR["PIR Motion<br/>(Movement)"]
        IR_Rx["IR Receiver<br/>(Commands)"]
        LCD["LCD1602<br/>(Display)"]
        LED["LEDs"]
        Motor_H["Motor"]
        Servo_H["Servo"]
    end
    
    subgraph Periph["🔗 ESP32 PERIPHERALS"]
        ADC_M["ADC<br/>Converter"]
        I2C_M["I2C Bus"]
        PWM_M["PWM"]
        RMT_M["RMT<br/>(IR Protocol)"]
        GPIO["GPIO"]
    end
    
    subgraph Comm["📡 COMMUNICATION"]
        WiFi["WiFi<br/>Module"]
        MQTT_M["MQTT<br/>Client"]
    end
    
    subgraph TaskCore["⚙️ TASKS & QUEUES"]
        T1["📊 Send Temp Task"]
        T2["📷 Send Photocell Task"]
        T3["📺 Display Task"]
        T4["💬 MQTT Task"]
        T5["📝 Log Task"]
        T6["🎮 IR Task"]
        
        Q1["temp_queue"]
        Q2["photo_queue"]
        Q3["display_queue"]
        Q4["mqtt_queue"]
        Q5["log_queue"]
        Q6["ir_queue"]
    end
    
    subgraph Cloud["☁️ CLOUD"]
        Broker["MQTT Broker"]
    end
    
    LM35 -->|Analog| ADC_M
    Photo -->|Analog| ADC_M
    ADC_M -->|Digital| T1
    ADC_M -->|Digital| T2
    
    PIR -->|GPIO| T6
    IR_Rx -->|Signal| RMT_M
    RMT_M -->|Decoded| T6
    
    LCD -->|I2C| I2C_M
    I2C_M -->|Control| T3
    
    T1 -->|Data| Q1
    T2 -->|Data| Q2
    T3 -->|Ready?| Q3
    T4 -->|Process| Q4
    T5 -->|Write| Q5
    T6 -->|Store| Q6
    
    Q1 -->|Read| T4
    Q2 -->|Read| T4
    Q3 -->|Read| T3
    Q4 -->|Publish| MQTT_M
    Q5 -->|Log| T5
    Q6 -->|Read| T4
    
    MQTT_M -->|WiFi| WiFi
    WiFi -->|TCP/MQTT| Broker
    Broker -->|Subscribe| MQTT_M
    
    T4 -->|PWM| PWM_M
    T4 -->|GPIO| GPIO
    T4 -->|RMT| RMT_M
    
    PWM_M --> Motor_H
    GPIO --> LED
    RMT_M --> Servo_H
    
    style Hardware fill:#FFE4B5
    style Periph fill:#B0E0E6
    style TaskCore fill:#DDA0DD
    style Comm fill:#F0E68C
    style Cloud fill:#FFB6C6
```

## Components Description

### 🔌 Hardware
- **LM35** - Temperature sensor, connected to ADC
- **Photocell** - Light level sensor, connected to ADC
- **PIR Motion** - Motion detector, connected to GPIO
- **IR Receiver** - Infrared signal receiver
- **LCD1602** - Display (2x16 characters), connected via I2C
- **LEDs** - Indicator LEDs
- **Motor** - DC motor, controlled by PWM
- **Servo** - Servo motor, controlled by RMT

### 🔗 ESP32 Peripherals
- **ADC** - Analog-to-digital converter (12-bit)
- **I2C Bus** - I²C bus for display communication
- **PWM** - Pulse-width modulation for motor control
- **RMT** - Remote Control Transceiver for IR and servo
- **GPIO** - General-purpose digital inputs/outputs

### ⚙️ FreeRTOS Tasks
- **Send Temp Task** - Reads LM35 temperature sensor and sends readings to MQTT and log queues
- **Send Photocell Task** - Reads light level sensor and sends to MQTT queue
- **Display Task** - Controls LCD1602 display (information output)
- **MQTT Task** - Main processing task, publishes sensor data to cloud and processes commands
- **Log Task** - Event logging to console
- **IR Task** - IR remote command processing with timeout-based watchdog reset

### 📡 Communication
- **WiFi** - Home network WiFi connectivity
- **MQTT** - Message exchange protocol (cloud)
- **MQTT Broker** - Cloud server for message storage

### 💾 Storage
- **NVS** - Non-volatile storage (flash memory) for configuration and WiFi/MQTT credentials

## Execution Flow

1. **Initialization**: `app_main()` initializes Task WDT (with idempotent error handling)
2. **NVS Load**: Non-volatile storage initialized for WiFi/MQTT credentials
3. **Module Start**: WiFi connected, MQTT client initialized and connected
4. **Hardware Init**: ADC, I2C, PWM, RMT drivers and sensors initialized
5. **Task Launch**: All FreeRTOS tasks started and run in parallel
6. **Data Collection**: Each task reads sensors at scheduled intervals
7. **Queue Exchange**: Data sent through FreeRTOS queues for safe inter-task communication
8. **Cloud Sync**: MQTT Task publishes sensor data to cloud broker
9. **Watchdog**: All tasks regularly reset watchdog timer (IR task has 4s timeout for graceful handling)

## FreeRTOS Queues

```
temp_store_queue       → temperature data
photo_cell_store_queue → light level
display_queue          → display commands
ir_queue               → IR remote commands
mqtt_queue             → commands from cloud
log_queue              → event logging
```

All queues converge in MQTT Task, which coordinates all system activities.
