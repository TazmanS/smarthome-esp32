#include "tasks/log_task/log_task.h"
#include "tasks/tasks.h"
#include "esp_log.h"

void logTask(void *pvParameters)
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