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
  nvs_init();

  modules_init();

  sensors_init();

  interrupts_init();

  tasks_init();
}
