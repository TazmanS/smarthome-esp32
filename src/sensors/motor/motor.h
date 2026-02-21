#ifndef MOTOR_H
#define MOTOR_H

#include "driver/gpio.h"
#include "driver/ledc.h"

typedef struct
{
  gpio_num_t pin;
  ledc_channel_t channel;
  bool is_active;
} motor_t;

void init_motors();

#endif