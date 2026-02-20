#include "send_photocell_task.h"
#include "tasks/tasks.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include <string.h>
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"
#include "sensors/photocell/photocell.h"

void send_photocell_task(void *pvParameters)
{
  while (1)
  {
    int light = photocell_read_light_level();
    sensor_data_t data = {
        .timestamp = xTaskGetTickCount()};
    strcpy(data.key, "sensor/photocell");
    data.value = (float)light;

    xQueueSend(mqttQueue, &data, portMAX_DELAY);

    xQueueSend(logQueue, &data, portMAX_DELAY);

    xQueueOverwrite(photoCellStoreQueue, &light);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}