#include "leds.h"
#include "driver/gpio.h"
#include "config/pins/pins.h"

LED DOOR_LED;
LED ROOF_LED;

void LED_init(LED *led, gpio_num_t pin)
{
  led->pin = pin;
  led->state = false;

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

void LED_on(LED *led)
{
  led->state = true;
  gpio_set_level(led->pin, 1);
}

void LED_off(LED *led)
{
  led->state = false;
  gpio_set_level(led->pin, 0);
}

void LED_toggle(LED *led)
{
  led->state = !led->state;
  gpio_set_level(led->pin, led->state ? 1 : 0);
}

void init_leds()
{
  LED_init(&DOOR_LED, DOOR_LED_PIN);
  LED_init(&ROOF_LED, ROOF_LED_PIN);
}