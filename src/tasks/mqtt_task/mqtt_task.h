/**
 * @file mqtt_task.h
 * @brief MQTT task interface
 * @details Declares the MQTT communication task function
 */

#ifndef MQTT_TASK_H
#define MQTT_TASK_H

/**
 * @brief MQTT communication task function
 * @details FreeRTOS task for handling MQTT message publishing and subscription
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void mqtt_task(void *pvParameters);

#endif