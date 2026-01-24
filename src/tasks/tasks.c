#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"

#include "tasks/send_temp/send_temp.h"

QueueHandle_t mqttQueue;
QueueHandle_t logQueue;

const int SendTempTaskStackSize = 4096;
const int SendTempTaskPriority = 5;

const int LogTaskStackSize = 4096;
const int LogTaskPriority = 3;

const int MqttTaskStackSize = 4096;
const int MqttTaskPriority = 4;

void tasks_init(void)
{
  mqttQueue = xQueueCreate(10, sizeof(sensor_data_t));
  logQueue = xQueueCreate(10, sizeof(sensor_data_t));

  xTaskCreate(sendTempTask, "SendTempTask", SendTempTaskStackSize, NULL, SendTempTaskPriority, NULL);
  xTaskCreate(logTask, "LogTask", LogTaskStackSize, NULL, LogTaskPriority, NULL);
  xTaskCreate(mqttTask, "MqttTask", MqttTaskStackSize, NULL, MqttTaskPriority, NULL);
}