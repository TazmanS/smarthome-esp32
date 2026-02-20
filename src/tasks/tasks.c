/**
 * @file tasks.c
 * @brief Task management implementation
 * @details Implements FreeRTOS task creation and initialization
 */

#include "tasks.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "stdio.h"

#include "tasks/send_temp_task/send_temp_task.h"
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"
#include "tasks/display_task/display_task.h"
#include "tasks/send_photocell_task/send_photocell_task.h"

QueueHandle_t mqttQueue;
QueueHandle_t logQueue;
QueueHandle_t tempStoreQueue;
QueueHandle_t displayQueue;
QueueHandle_t photoCellStoreQueue;

const int SendTempTaskStackSize = 4096;
const int SendTempTaskPriority = 5;

const int SendPhotoCellTaskStackSize = 4096;
const int SendPhotoCellTaskPriority = 5;

const int DisplayTaskStackSize = 4096;
const int DisplayTaskPriority = 4;

const int LogTaskStackSize = 4096;
const int LogTaskPriority = 2;

const int MqttTaskStackSize = 4096;
const int MqttTaskPriority = 4;

/**
 * @brief Initializes all application tasks
 * @details Creates and starts FreeRTOS tasks for
 *          Temperature sensing,
 *          MQTT communication,
 *          Logging
 * @return void
 */
void tasks_init(void)
{
  mqttQueue = xQueueCreate(10, sizeof(sensor_data_t));
  logQueue = xQueueCreate(10, sizeof(sensor_data_t));
  displayQueue = xQueueCreate(1, sizeof(DisplayScreenState));
  tempStoreQueue = xQueueCreate(1, sizeof(float));
  photoCellStoreQueue = xQueueCreate(1, sizeof(int));

  configASSERT(mqttQueue != NULL);
  configASSERT(logQueue != NULL);
  configASSERT(displayQueue != NULL);
  configASSERT(tempStoreQueue != NULL);
  configASSERT(photoCellStoreQueue != NULL);

  configASSERT(xTaskCreate(send_temp_task, "SendTempTask", SendTempTaskStackSize, NULL, SendTempTaskPriority, NULL) == pdPASS);
  configASSERT(xTaskCreate(send_photocell_task, "SendPhotoCellTask", SendPhotoCellTaskStackSize, NULL, SendPhotoCellTaskPriority, NULL) == pdPASS);
  configASSERT(xTaskCreate(display_task, "DisplayTask", DisplayTaskStackSize, NULL, DisplayTaskPriority, NULL) == pdPASS);

  configASSERT(xTaskCreate(log_task, "LogTask", LogTaskStackSize, NULL, LogTaskPriority, NULL) == pdPASS);
  configASSERT(xTaskCreate(mqtt_task, "MqttTask", MqttTaskStackSize, NULL, MqttTaskPriority, NULL) == pdPASS);
}