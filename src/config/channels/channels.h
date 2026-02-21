#ifndef CHANNELS_H
#define CHANNELS_H

#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

extern const adc_channel_t LM35_ADC_CHANNEL;      /** ADC channel for LM35 sensor */
extern const adc_channel_t PHOTOCELL_ADC_CHANNEL; /** ADC channel for photocell sensor */

extern const ledc_channel_t WINDOW_SERVO_CHANNEL; /** LEDC channel for window servo control */
extern const ledc_channel_t FAN_MOTOR_CHANNEL;    /** LEDC channel for fan motor control */

#endif