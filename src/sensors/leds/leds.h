#ifndef LEDS_H
#define LEDS_H

#include "driver/gpio.h"

typedef struct
{
  gpio_num_t pin;
  bool state;
} LED;

void LED_on(LED *led);
void LED_off(LED *led);
void LED_toggle(LED *led);
void init_leds();

extern LED DOOR_LED;
extern LED ROOF_LED;

#endif