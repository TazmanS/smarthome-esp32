/**
 * @file main.c
 * @brief Main application entry point for Smart Home ESP32 project
 * @details Initializes hardware components (ADC, NVS), WiFi connectivity,
 *          MQTT client, and task management system.
 */

#include "helpers/nvs/nvs.h"
#include "modules/modules.h"
#include "sensors/sensors.h"
#include "interrupts/interrupts.h"
#include "tasks/tasks.h"
#include "freertos/FreeRTOS.h"
#include "esp_task_wdt.h"
#include "esp_log.h"

static const char *TAG = "main";

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
  const esp_task_wdt_config_t twdt_cfg = {
      .timeout_ms = 5000,
      .idle_core_mask = (1 << portNUM_PROCESSORS) - 1,
      .trigger_panic = true,
  };

  esp_err_t twdt_err = esp_task_wdt_init(&twdt_cfg);
  if (twdt_err == ESP_ERR_INVALID_STATE)
  {
    ESP_LOGW(TAG, "Task WDT already initialized, continuing with existing configuration");
  }
  else
  {
    ESP_ERROR_CHECK(twdt_err);
  }

  nvs_init();

  modules_init();

  sensors_init();

  interrupts_init();

  tasks_init();
}
