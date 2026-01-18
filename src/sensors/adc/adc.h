#pragma once

#include "driver/adc.h"
#include "esp_adc_cal.h"

void adc_init();

extern esp_adc_cal_characteristics_t *adc_chars;
extern adc1_channel_t ADC_CHANNEL;