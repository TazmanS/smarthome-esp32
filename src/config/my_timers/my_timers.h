#ifndef MY_TIMERS_H
#define MY_TIMERS_H

#include "driver/ledc.h"

extern const ledc_timer_t TIMER_SERVO_WINDOW; /**< LEDC timer for servo control */
extern const ledc_timer_t TIMER_FAN_MOTOR;    /**< LEDC timer for motor control */

#endif