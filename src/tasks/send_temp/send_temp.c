#include "send_temp.h"
#include "tasks/tasks.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include <string.h>
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"
#include "sensors/lm35/lm35.h"

void sendTempTask(void *pvParameters)
{
  while (1)
  {
    float temp = lm35_read_temperature();
    sensor_data_t data = {
        .timestamp = xTaskGetTickCount()};
    strcpy(data.key, "temperature");
    data.value = temp;

    xQueueSend(mqttQueue, &data, portMAX_DELAY);

    xQueueSend(logQueue, &data, portMAX_DELAY);

    // TODO take delay from env
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
