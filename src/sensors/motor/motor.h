#ifndef MOTOR_H
#define MOTOR_H

#include "driver/gpio.h"
#include "driver/ledc.h"

typedef struct
{
  gpio_num_t pin_INA;
  gpio_num_t pin_INB;
  ledc_channel_t channel_INA;
  ledc_channel_t channel_INB;
  bool is_active;
  bool is_reverse;
  int power;
} motor_t;

extern motor_t motor_fan;

void motors_init();
void motor_set_power(motor_t *motor, int power);
void motor_turn_off(motor_t *motor);
void motor_turn_on(motor_t *motor);

#endif