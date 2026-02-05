/**
 * @file buttons.h
 * @brief Button interrupt helper
 * @details Provides a small abstraction for button objects and initialization
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "driver/gpio.h"

/**
 * @brief Button object
 */
typedef struct
{
  gpio_num_t pin;
  void (*callback)(void *);
  void *callback_arg;
} Button;

/**
 * @brief Initialize button interrupts
 * @return void
 */
void buttons_interrupt_init();
extern Button DOOR_BUTTON;
extern Button ROOF_BUTTON;

#endif