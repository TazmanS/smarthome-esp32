/**
 * @file adc.h
 * @brief ADC (Analog-to-Digital Converter) interface
 * @details Declares functions for initializing and reading analog sensor values
 */

#ifndef ADC_H
#define ADC_H

#include "driver/gpio.h"
#include "esp_adc/adc_oneshot.h"

typedef struct
{
  gpio_num_t pin;
  adc_channel_t channel;
  adc_atten_t attenuation;
  adc_bitwidth_t bitwidth;
} ADC_MODULE;

extern adc_oneshot_unit_handle_t adc_handle;

/**
 * @brief Initializes ADC hardware
 * @details Configures ADC channels and sampling parameters for sensor readings
 * @return void
 */
void adc_init();
void adc_init_channel(ADC_MODULE *adc_module);

#endif