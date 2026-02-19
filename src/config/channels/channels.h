#ifndef CHANNELS_H
#define CHANNELS_H

#include "esp_adc/adc_oneshot.h"

extern const adc_channel_t LM35_ADC_CHANNEL;      /** ADC channel for LM35 sensor */
extern const adc_channel_t PHOTOCELL_ADC_CHANNEL; /** ADC channel for photocell sensor */

#endif