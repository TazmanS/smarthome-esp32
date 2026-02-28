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
#include "tasks/ir_task/ir_task.h"

#include "sensors/ir_receiver/ir_receiver.h"

QueueHandle_t mqtt_queue;
QueueHandle_t log_queue;
QueueHandle_t temp_store_queue;
QueueHandle_t display_queue;
QueueHandle_t photo_cell_store_queue;
QueueHandle_t ir_queue;

const int send_temp_task_stack_size = 4096;
const int send_temp_task_priority = 5;

const int send_photocell_task_stack_size = 4096;
const int send_photocell_task_priority = 5;

const int display_task_stack_size = 4096;
const int display_task_priority = 4;

const int log_task_stack_size = 4096;
const int log_task_priority = 2;

const int mqtt_task_stack_size = 4096;
const int mqtt_task_priority = 4;

const int ir_task_stack_size = 4096;
const int ir_task_priority = 3;

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
  mqtt_queue = xQueueCreate(10, sizeof(sensor_data_t));
  log_queue = xQueueCreate(10, sizeof(sensor_data_t));
  display_queue = xQueueCreate(1, sizeof(DisplayScreenState));
  temp_store_queue = xQueueCreate(1, sizeof(float));
  photo_cell_store_queue = xQueueCreate(1, sizeof(int));
  ir_queue = xQueueCreate(5, sizeof(ir_button_t));

  configASSERT(mqtt_queue != NULL);
  configASSERT(log_queue != NULL);
  configASSERT(display_queue != NULL);
  configASSERT(temp_store_queue != NULL);
  configASSERT(photo_cell_store_queue != NULL);
  configASSERT(ir_queue != NULL);

  // configASSERT(xTaskCreate(send_temp_task, "SendTempTask", send_temp_task_stack_size, NULL, send_temp_task_priority, NULL) == pdPASS);
  // configASSERT(xTaskCreate(send_photocell_task, "SendPhotoCellTask", send_photocell_task_stack_size, NULL, send_photocell_task_priority, NULL) == pdPASS);
  // configASSERT(xTaskCreate(display_task, "DisplayTask", display_task_stack_size, NULL, display_task_priority, NULL) == pdPASS);
  configASSERT(xTaskCreate(ir_task, "IrTask", ir_task_stack_size, NULL, ir_task_priority, NULL) == pdPASS);

  configASSERT(xTaskCreate(log_task, "LogTask", log_task_stack_size, NULL, log_task_priority, NULL) == pdPASS);
  configASSERT(xTaskCreate(mqtt_task, "MqttTask", mqtt_task_stack_size, NULL, mqtt_task_priority, NULL) == pdPASS);
}