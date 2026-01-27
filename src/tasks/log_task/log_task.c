/**
 * @file log_task.c
 * @brief Logging task implementation
 * @details Implements FreeRTOS task for logging application events and status
 */

#include "log_task.h"
#include "tasks/tasks.h"
#include "esp_log.h"

/**
 * @brief Logging task function
 * @details FreeRTOS task that periodically logs application status and events
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void log_task(void *pvParameters)
{
  while (1)
  {
    sensor_data_t data;
    if (xQueueReceive(logQueue, &data, portMAX_DELAY))
    {
      ESP_LOGI("logTask", "%s: %.2f", data.key, data.value);
    }
  }
}