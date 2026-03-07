/**
 * @file my_timers.c
 * @brief LEDC timer implementation
 */

#include "my_timers.h"
#include "driver/ledc.h"

/** @brief LEDC timer 0 for window servo */
const ledc_timer_t TIMER_SERVO_WINDOW = LEDC_TIMER_0;
/** @brief LEDC timer 1 for fan motor */
const ledc_timer_t TIMER_FAN_MOTOR = LEDC_TIMER_1;