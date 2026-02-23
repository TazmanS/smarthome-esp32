#include "my_timers.h"
#include "driver/ledc.h"

const ledc_timer_t SERVO_WINDOW_TIMER = LEDC_TIMER_0; /**< LEDC timer for servo control */
const ledc_timer_t MOTOR_FAN_TIMER = LEDC_TIMER_1;    /**< LEDC timer for motor control */