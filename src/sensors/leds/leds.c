/**
 * @file leds.c
 * @brief LED control implementation
 * @details Implements simple LED API (init, on, off, toggle with debounce)
 */

#include "leds.h"
#include "driver/gpio.h"
#include "config/pins/pins.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"

led_t led_door;
led_t led_roof;

#define LED_DEBOUNCE_TIME_US 200000

static portMUX_TYPE s_led_lock = portMUX_INITIALIZER_UNLOCKED;

/**
 * @brief Initialize an LED object and configure GPIO
 * @param[out] led Pointer to LED object to initialize
 * @param[in] pin GPIO pin used by LED
 * @return void
 */
void LED_init(led_t *led, gpio_num_t pin)
{
  led->pin = pin;
  led->level = false;
  led->last_toggle_time_us = 0;
  led->state = LED_DEFAULT;

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
void LED_on(led_t *led)
{
  taskENTER_CRITICAL(&s_led_lock);
  if (led->state == LED_DEFAULT || led->state == LED_ON)
  {
    led->level = true;
    gpio_set_level(led->pin, 1);
  }
  taskEXIT_CRITICAL(&s_led_lock);
}

/**
 * @brief Turn LED off
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_off(led_t *led)
{
  taskENTER_CRITICAL(&s_led_lock);
  if (led->state == LED_DEFAULT || led->state == LED_OFF)
  {
    led->level = false;
    gpio_set_level(led->pin, 0);
  }
  taskEXIT_CRITICAL(&s_led_lock);
}

/**
 * @brief Toggle LED state with debounce
 * @param[in,out] led Pointer to LED object
 * @return void
 */
void LED_toggle(led_t *led)
{
  taskENTER_CRITICAL(&s_led_lock);
  if (led->state == LED_DEFAULT)
  {
    int64_t now = esp_timer_get_time();

    if (now - led->last_toggle_time_us > LED_DEBOUNCE_TIME_US)
    {
      led->last_toggle_time_us = now;
      led->level = !led->level;
      gpio_set_level(led->pin, led->level ? 1 : 0);
    }
  }
  taskEXIT_CRITICAL(&s_led_lock);
}

void LED_on_from_isr(led_t *led)
{
  taskENTER_CRITICAL_ISR(&s_led_lock);
  if (led->state == LED_DEFAULT || led->state == LED_ON)
  {
    led->level = true;
    gpio_set_level(led->pin, 1);
  }
  taskEXIT_CRITICAL_ISR(&s_led_lock);
}

void LED_toggle_from_isr(led_t *led)
{
  taskENTER_CRITICAL_ISR(&s_led_lock);
  if (led->state == LED_DEFAULT)
  {
    int64_t now = esp_timer_get_time();

    if (now - led->last_toggle_time_us > LED_DEBOUNCE_TIME_US)
    {
      led->last_toggle_time_us = now;
      led->level = !led->level;
      gpio_set_level(led->pin, led->level ? 1 : 0);
    }
  }
  taskEXIT_CRITICAL_ISR(&s_led_lock);
}

/**
 * @brief Initialize all application LEDs
 * @return void
 */
void leds_init()
{
  LED_init(&led_door, PIN_LED_DOOR);
  LED_init(&led_roof, PIN_LED_ROOF);
}