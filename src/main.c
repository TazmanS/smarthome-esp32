/**
 * @file main.c
 * @brief Main application entry point for Smart Home ESP32 project
 * @details Initializes hardware components (ADC, NVS), WiFi connectivity,
 *          MQTT client, and task management system.
 */

#include "nvs_flash.h"

#include "sensors/wifi/wifi.h"
#include "sensors/mqtt/mqtt.h"
#include "sensors/adc/adc.h"

#include "secrets/secrets.h"
#include "tasks/tasks.h"

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
  wifi_init_sta(WIFI_SSID, WIFI_PASS);

  mqtt_app_start();

  tasks_init();
}
