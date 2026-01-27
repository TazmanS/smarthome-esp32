/**
 * @file send_temp.h
 * @brief Temperature sending task interface
 * @details Declares the temperature reading and transmission task function
 */

#ifndef SEND_TEMP_H
#define SEND_TEMP_H

/**
 * @brief Temperature reading and transmission task function
 * @details FreeRTOS task that reads LM35 temperature sensor and sends data via MQTT
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void send_temp_task(void *pvParameters);

#endif