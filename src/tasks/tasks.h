/**
 * @file tasks.h
 * @brief Task management interface
 * @details Declares functions for initializing and managing FreeRTOS tasks
 */

#ifndef TASKS_H
#define TASKS_H

#include "freertos/FreeRTOS.h"

/**
 * @brief Initializes all application tasks
 * @details Creates and starts FreeRTOS tasks for temperature sensing,
 *          MQTT communication, and logging
 * @return void
 */
void tasks_init(void);

extern QueueHandle_t mqtt_queue;
extern QueueHandle_t log_queue;
extern QueueHandle_t temp_store_queue;
extern QueueHandle_t display_queue;
extern QueueHandle_t photo_cell_store_queue;
extern QueueHandle_t ir_queue;

/**
 * @brief Structure to hold sensor data
 */
typedef struct
{
  char key[32];       /**< Key identifying the sensor */
  float value;        /**< Sensor value */
  uint32_t timestamp; /**< Timestamp of the reading */
} sensor_data_t;

#endif
