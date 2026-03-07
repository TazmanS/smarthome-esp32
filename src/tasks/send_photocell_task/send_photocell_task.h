/**
 * @file send_photocell_task.h
 * @brief Photocell sensor reading task interface
 * @details Declares the task for reading light sensor and sending data
 */

#ifndef SEND_PHOTOCELL_TASK_H
#define SEND_PHOTOCELL_TASK_H

/**
 * @brief Photocell reading and transmission task
 * @details FreeRTOS task that reads photocell light level and transmits via MQTT
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void send_photocell_task(void *pvParameters);

#endif