/**
 * @file tasks.c
 * @brief Task management implementation
 * @details Implements FreeRTOS task creation and initialization
 */

#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"

#include "tasks/send_temp/send_temp.h"
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"

QueueHandle_t mqttQueue;
QueueHandle_t logQueue;

const int SendTempTaskStackSize = 4096;
const int SendTempTaskPriority = 5;

const int LogTaskStackSize = 4096;
const int LogTaskPriority = 3;

const int MqttTaskStackSize = 4096;
const int MqttTaskPriority = 4;

/**
 * @brief Initializes all application tasks
 * @details Creates and starts FreeRTOS tasks for temperature sensing,
 *          MQTT communication, and logging
 * @return void
 */
void tasks_init(void)
{
  mqttQueue = xQueueCreate(10, sizeof(sensor_data_t));
  logQueue = xQueueCreate(10, sizeof(sensor_data_t));

  xTaskCreate(send_temp_task, "SendTempTask", SendTempTaskStackSize, NULL, SendTempTaskPriority, NULL);
  xTaskCreate(log_task, "LogTask", LogTaskStackSize, NULL, LogTaskPriority, NULL);
  xTaskCreate(mqtt_task, "MqttTask", MqttTaskStackSize, NULL, MqttTaskPriority, NULL);
}