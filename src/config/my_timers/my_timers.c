#include "my_timers.h"
#include "driver/ledc.h"

const ledc_timer_t TIMER_SERVO_WINDOW = LEDC_TIMER_0; /**< LEDC timer for servo control */
const ledc_timer_t TIMER_FAN_MOTOR = LEDC_TIMER_1;    /**< LEDC timer for motor control */