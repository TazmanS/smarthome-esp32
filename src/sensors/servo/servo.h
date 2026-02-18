#ifndef SERVO_H
#define SERVO_H

#include "driver/ledc.h"

/**
 * @brief Servo object
 */
typedef struct
{
  gpio_num_t gpio_pin;
  ledc_channel_t channel;
} Servo;

void init_servo();
void set_servo_angle(Servo *servo, int angle);

extern Servo window_servo;

#endif