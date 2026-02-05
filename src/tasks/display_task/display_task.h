/**
 * @file display_task.h
 * @brief Display task interface
 * @details Declares the FreeRTOS task used to update the LCD display
 */

#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

/**
 * @brief Display task function
 * @details Receives temperature samples and updates the LCD accordingly
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters);

#endif