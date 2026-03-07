#ifndef CHANNELS_H
#define CHANNELS_H

#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

extern const adc_channel_t CHANNEL_ADC_LM35;      /** ADC channel for LM35 sensor */
extern const adc_channel_t CHANNEL_ADC_PHOTOCELL; /** ADC channel for photocell sensor */

extern const ledc_channel_t CHANNEL_SERVO_WINDOW;  /** LEDC channel for window servo control */
extern const ledc_channel_t CHANNEL_MOTOR_FAN_INA; /** LEDC channel for fan motor INA control */
extern const ledc_channel_t CHANNEL_MOTOR_FAN_INB; /** LEDC channel for fan motor INB control */

#endif