/**
 * @file log_task.h
 * @brief Logging task interface
 * @details Declares the logging task function for monitoring application events
 */

#ifndef LOG_TASK_H
#define LOG_TASK_H

/**
 * @brief Logging task function
 * @details FreeRTOS task that periodically logs application status and events
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void log_task(void *pvParameters);

#endif