/**
 * @file leds.h
 * @brief LED control API
 * @details Provides simple LED abstraction and functions to control LEDs used in the project
 */

#ifndef LEDS_H
#define LEDS_H

#include "driver/gpio.h"

/**
 * @brief LED object
 */
typedef struct
{
  gpio_num_t pin;
  bool state;
  int64_t last_toggle_time_us;
} led_t;

/**
 * @brief Turn LED on
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_on(led_t *led);
/**
 * @brief Turn LED off
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_off(led_t *led);
/**
 * @brief Toggle LED state (with debounce)
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_toggle(led_t *led);
/**
 * @brief Initialize application LEDs
 * @return void
 */
void init_leds();

extern led_t door_led;
extern led_t roof_led;

#endif