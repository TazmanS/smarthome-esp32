/**
 * @file ir_task.h
 * @brief Infrared receiver processing task interface
 * @details Declares the task for receiving and processing IR remote commands
 */

#ifndef IR_TASK_H
#define IR_TASK_H

/**
 * @brief IR receiver processing task
 * @details FreeRTOS task that processes IR remote signals and triggers actions
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void ir_task(void *pvParameters);

#endif