#ifndef BUTTONS_H
#define BUTTONS_H

#include "driver/gpio.h"

typedef struct
{
  gpio_num_t pin;
  void (*callback)(void *);
  void *callback_arg;
} Button;

void buttons_interrupt_init();
extern Button DOOR_BUTTON;
extern Button ROOF_BUTTON;

#endif