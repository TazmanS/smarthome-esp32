/**
 * @file channels.c
 * @brief ADC and LEDC channel implementation
 */

#include "channels.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

/** @brief ADC channel 0 for LM35 temperature sensor */
const adc_channel_t CHANNEL_ADC_LM35 = ADC_CHANNEL_0;
/** @brief ADC channel 3 for photocell light sensor */
const adc_channel_t CHANNEL_ADC_PHOTOCELL = ADC_CHANNEL_3;

/** @brief LEDC channel 0 for window servo */
const ledc_channel_t CHANNEL_SERVO_WINDOW = LEDC_CHANNEL_0;
/** @brief LEDC channel 1 for fan motor INA */
const ledc_channel_t CHANNEL_MOTOR_FAN_INA = LEDC_CHANNEL_1;
/** @brief LEDC channel 2 for fan motor INB */
const ledc_channel_t CHANNEL_MOTOR_FAN_INB = LEDC_CHANNEL_2;