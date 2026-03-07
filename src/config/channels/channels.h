/**
 * @file channels.h
 * @brief ADC and LEDC channel configuration
 * @details Defines channel assignments for ADC sensors and PWM outputs
 */

#ifndef CHANNELS_H
#define CHANNELS_H

#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

/** @brief ADC channel for LM35 temperature sensor */
extern const adc_channel_t CHANNEL_ADC_LM35;
/** @brief ADC channel for photocell light sensor */
extern const adc_channel_t CHANNEL_ADC_PHOTOCELL;

/** @brief LEDC channel for window servo PWM */
extern const ledc_channel_t CHANNEL_SERVO_WINDOW;
/** @brief LEDC channel for fan motor INA control */
extern const ledc_channel_t CHANNEL_MOTOR_FAN_INA;
/** @brief LEDC channel for fan motor INB control */
extern const ledc_channel_t CHANNEL_MOTOR_FAN_INB;

#endif