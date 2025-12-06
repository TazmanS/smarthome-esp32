#pragma once
#include "driver/adc.h"
#include "esp_err.h"

esp_err_t lm35_init(adc1_channel_t channel);
esp_err_t lm35_read_temperature(adc1_channel_t channel, float *temperature);
