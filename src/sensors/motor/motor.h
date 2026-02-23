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

extern motor_t fan_motor;

void init_motors();
void set_motor_power(motor_t *motor, int power);

#endif