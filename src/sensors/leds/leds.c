/**
 * @file leds.c
 * @brief LED control implementation
 * @details Implements simple LED API (init, on, off, toggle with debounce)
 */

#include "leds.h"
#include "driver/gpio.h"
#include "config/pins/pins.h"
#include "esp_timer.h"

LED door_led;
LED roof_led;

#define LED_DEBOUNCE_TIME_US 200000

/**
 * @brief Initialize an LED object and configure GPIO
 * @param[out] led Pointer to LED object to initialize
 * @param[in] pin GPIO pin used by LED
 * @return void
 */
void LED_init(LED *led, gpio_num_t pin)
{
  led->pin = pin;
  led->state = false;
  led->last_toggle_time_us = 0;

  gpio_config_t io_config = {
      .pin_bit_mask = (1ULL << pin),
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&io_config);

  gpio_set_level(pin, 0);
}

/**
 * @brief Turn LED on
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_on(LED *led)
{
  led->state = true;
  gpio_set_level(led->pin, 1);
}

/**
 * @brief Turn LED off
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_off(LED *led)
{
  led->state = false;
  gpio_set_level(led->pin, 0);
}

/**
 * @brief Toggle LED state with debounce
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_toggle(LED *led)
{
  int64_t now = esp_timer_get_time();

  if (now - led->last_toggle_time_us > LED_DEBOUNCE_TIME_US)
  {
    led->last_toggle_time_us = now;
    led->state = !led->state;
    gpio_set_level(led->pin, led->state ? 1 : 0);
  }
}

/**
 * @brief Initialize all application LEDs
 * @return void
 */
void init_leds()
{
  LED_init(&door_led, DOOR_LED_PIN);
  LED_init(&roof_led, ROOF_LED_PIN);
}