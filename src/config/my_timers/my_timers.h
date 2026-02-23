#ifndef MY_TIMERS_H
#define MY_TIMERS_H

#include "driver/ledc.h"

extern const ledc_timer_t SERVO_WINDOW_TIMER; /**< LEDC timer for servo control */
extern const ledc_timer_t MOTOR_FAN_TIMER;    /**< LEDC timer for motor control */

#endif