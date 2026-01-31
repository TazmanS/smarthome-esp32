/**
 * @file send_temp.c
 * @brief Temperature sending task implementation
 * @details Implements FreeRTOS task for temperature sensing and MQTT transmission
 */

#include "send_temp.h"
#include "tasks/tasks.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include <string.h>
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"
#include "sensors/lm35/lm35.h"

/**
 * @brief Temperature reading and transmission task function
 * @details FreeRTOS task that reads LM35 temperature sensor and sends data via MQTT + Logs + store laste temp
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void send_temp_task(void *pvParameters)
{
  while (1)
  {
    float temp = lm35_read_temperature();
    sensor_data_t data = {
        .timestamp = xTaskGetTickCount()};
    strcpy(data.key, "sensor/temperature");
    data.value = temp;

    xQueueSend(mqttQueue, &data, portMAX_DELAY);

    xQueueSend(logQueue, &data, portMAX_DELAY);

    xQueueOverwrite(tempStoreQueue, &temp);

    // TODO take delay from env
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
