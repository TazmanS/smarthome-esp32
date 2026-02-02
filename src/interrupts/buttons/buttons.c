#include "buttons.h"
#include "sensors/leds/leds.h"
#include "config/pins/pins.h"

Button DOOR_BUTTON;
Button ROOF_BUTTON;

void Button_init(Button *btn, gpio_num_t pin, void (*callback)(void *), void *arg)
{
  btn->pin = pin;
  btn->callback = callback;
  btn->callback_arg = arg;

  gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL << pin),
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_NEGEDGE};
  gpio_config(&io_conf);

  gpio_install_isr_service(0);
  gpio_isr_handler_add(pin, callback, arg);
}

void button_pressed(void *arg)
{
  LED *led = (LED *)arg;
  LED_toggle(led);
}

void buttons_interrupt_init()
{
  Button_init(&DOOR_BUTTON, DOOR_BUTTON_PIN, button_pressed, &DOOR_LED);
  Button_init(&ROOF_BUTTON, ROOF_BUTTON_PIN, button_pressed, &ROOF_LED);
}