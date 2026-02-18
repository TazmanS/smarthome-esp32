/**
 * @file main.c
 * @brief Main application entry point for Smart Home ESP32 project
 * @details Initializes hardware components (ADC, NVS), WiFi connectivity,
 *          MQTT client, and task management system.
 */

#include "nvs_flash.h"

#include "modules/wifi/wifi.h"
#include "modules/mqtt/mqtt.h"
#include "modules/adc/adc.h"
#include "modules/my_i2c/my_i2c.h"
#include "modules/pwm/pwm.h"

#include "config/secrets/secrets.h"
#include "tasks/tasks.h"

#include "sensors/lcd1602/lcd1602.h"
#include "sensors/leds/leds.h"
#include "sensors/pir_motion/pir_motion.h"
#include "sensors/servo/servo.h"

#include "interrupts/buttons/buttons.h"

/**
 * @brief Main application entry point
 * @details Performs the following initialization sequence:
 *          1. Initializes ADC for sensor readings
 *          2. Initializes NVS (Non-Volatile Storage) flash memory
 *          3. Establishes WiFi connection using stored credentials
 *          4. Starts MQTT client for IoT communication
 *          5. Initializes and starts application tasks
 *
 * @note This function is called by the ESP-IDF framework and never returns
 * @return void
 */
void app_main(void)
{
  adc_init();

  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  // wifi_init_sta(WIFI_SSID, WIFI_PASS);

  // mqtt_app_start();

  i2c_init();

  lcd1602_init(I2C_NUM_0);

  init_leds();

  buttons_interrupt_init();

  pir_motion_init();

  init_pwm_timer();
  // init_servo();
  init_pwm_channel(&window_servo);

  tasks_init();
}
