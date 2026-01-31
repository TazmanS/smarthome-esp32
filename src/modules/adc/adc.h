/**
 * @file adc.h
 * @brief ADC (Analog-to-Digital Converter) interface
 * @details Declares functions for initializing and reading analog sensor values
 */

#ifndef ADC_H
#define ADC_H

#include "driver/adc.h"
#include "esp_adc_cal.h"

/**
 * @brief Initializes ADC hardware
 * @details Configures ADC channels and sampling parameters for sensor readings
 * @return void
 */
void adc_init(void);

extern esp_adc_cal_characteristics_t *adc_chars;
extern adc1_channel_t ADC_CHANNEL;

#endif