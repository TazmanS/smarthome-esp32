/**
 * @file buttons.c
 * @brief Button interrupt implementation
 * @details Implements button initialization and ISR callback used to toggle LEDs
 */

#include "buttons.h"
#include "sensors/leds/leds.h"
#include "config/pins/pins.h"
#include "esp_attr.h"

Button door_button;
Button roof_button;

/**
 * @brief Initialize a Button object and register ISR
 * @param[out] btn Pointer to Button object to initialize
 * @param[in] pin GPIO pin used by the button
 * @param[in] callback ISR callback function
 * @param[in] arg Argument passed to callback
 * @return void
 */
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

/**
 * @internal
 * @brief ISR fired when a button is pressed; toggles linked LED
 */
void IRAM_ATTR button_pressed(void *arg)
{
  LED *led = (LED *)arg;
  LED_toggle(led);
}

/**
 * @brief Initialize button interrupts for application buttons
 * @return void
 */
void buttons_interrupt_init()
{
  Button_init(&door_button, DOOR_BUTTON_PIN, button_pressed, &door_led);
  Button_init(&roof_button, ROOF_BUTTON_PIN, button_pressed, &roof_led);
}