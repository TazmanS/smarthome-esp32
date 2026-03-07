/**
 * @file my_timers.h
 * @brief LEDC timer configuration
 * @details Defines LEDC timers used for PWM control of servos and motors
 */

#ifndef MY_TIMERS_H
#define MY_TIMERS_H

#include "driver/ledc.h"

/** @brief LEDC timer for window servo */
extern const ledc_timer_t TIMER_SERVO_WINDOW;
/** @brief LEDC timer for fan motor */
extern const ledc_timer_t TIMER_FAN_MOTOR;

#endif