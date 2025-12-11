#pragma once
#include "driver/adc.h"
#include "esp_err.h"

void lm35_init(adc1_channel_t channel);
float lm35_read_temperature(adc1_channel_t channel);
