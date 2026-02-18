#ifndef PWM_H
#define PWM_H

#include "sensors/servo/servo.h"

void init_pwm_timer();
void init_pwm_channel(Servo *servo);

#endif