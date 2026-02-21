/**
 * @file pwm.h
 * @brief PWM (Pulse Width Modulation) interface
 * @details Declares functions for initializing PWM timers and channels for servo control
 */

#ifndef PWM_H
#define PWM_H

#include "sensors/servo/servo.h"

/**
 * @brief Initialize PWM timer for servo control
 * @return void
 */
void init_pwm_timer();

/**
 * @brief Initialize PWM channel for a specific servo
 * @param[in,out] servo Pointer to Servo object to configure
 * @return void
 */
void init_pwm_channel(gpio_num_t gpio_pin, ledc_channel_t channel);

#endif