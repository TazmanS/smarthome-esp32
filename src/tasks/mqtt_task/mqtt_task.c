#include "mqtt_task.h"
#include "tasks/tasks.h"
#include "sensors/mqtt/mqtt.h"

void mqttTask(void *pvParameters)
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