/**
 * @file lm35.h
 * @brief LM35 temperature sensor interface
 * @details Declares functions for reading temperature from LM35 analog sensor
 */

#ifndef LM35_H
#define LM35_H

#include "driver/adc.h"
#include "esp_err.h"

/**
 * @brief Reads temperature from LM35 sensor
 * @details Performs ADC conversion and converts raw value to Celsius
 * @return float Temperature value in Celsius
 */
float lm35_read_temperature(void);

/**
 * @brief Initializes LM35 sensor
 * @details Configures ADC channel and parameters for LM35 readings
 * @return void
 */
void init_lm35();

#endif
