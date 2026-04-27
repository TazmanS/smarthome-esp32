/**
 * @file mqtt_task.c
 * @brief MQTT task implementation
 * @details Implements FreeRTOS task for MQTT communication handling
 */

#include "mqtt_task.h"
#include "tasks/tasks.h"
#include "modules/mqtt/mqtt.h"
#include "esp_task_wdt.h"

/**
 * @brief MQTT communication task function
 * @details FreeRTOS task for handling MQTT message publishing and subscription
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void mqtt_task(void *pvParameters)
{
  ESP_ERROR_CHECK(esp_task_wdt_add(NULL));

  while (1)
  {
    sensor_data_t data;
    if (xQueueReceive(mqtt_queue, &data, portMAX_DELAY))
    {
      char buf[64];
      snprintf(buf, sizeof(buf), "{\"%s\": %.2f}", data.key, data.value);

      mqtt_publish(data.key, buf);
    }

    esp_task_wdt_reset();
  }
}