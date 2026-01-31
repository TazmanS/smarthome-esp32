/**
 * @file mqtt_task.c
 * @brief MQTT task implementation
 * @details Implements FreeRTOS task for MQTT communication handling
 */

#include "mqtt_task.h"
#include "tasks/tasks.h"
#include "modules/mqtt/mqtt.h"

/**
 * @brief MQTT communication task function
 * @details FreeRTOS task for handling MQTT message publishing and subscription
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void mqtt_task(void *pvParameters)
{
  while (1)
  {
    sensor_data_t data;
    if (xQueueReceive(mqttQueue, &data, portMAX_DELAY))
    {
      char buf[64];
      snprintf(buf, sizeof(buf), "{\"%s\": %.2f}", data.key, data.value);

      mqtt_publish(data.key, buf);
    }
  }
}