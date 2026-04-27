/**
 * @file pir_motion.c
 * @brief PIR motion sensor implementation
 * @details Implements interrupt handling and state reading for the PIR sensor
 */

#include "pir_motion.h"
#include "driver/gpio.h"
#include "config/pins/pins.h"
#include "esp_attr.h"
#include "sensors/leds/leds.h"
#include "esp_timer.h"
#include "esp_err.h"

#define PIR_DEBOUNCE_TIME_US 200000
static int64_t last_toggle_time_us = 0;

/**
 * @internal
 * @brief ISR callback for PIR motion events
 */
void IRAM_ATTR pir_motion_callback(void *arg)
{
  uint64_t now = esp_timer_get_time();
  if (now - last_toggle_time_us > PIR_DEBOUNCE_TIME_US)
  {
    LED_on_from_isr(&led_door);
    last_toggle_time_us = now;
  }
}

/**
 * @brief Initialize PIR motion sensor interrupt
 * @return void
 */
void pir_motion_init()
{
  gpio_config_t io_config = {
      .pin_bit_mask = (1ULL << PIN_PIR_MOTION),
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .intr_type = GPIO_INTR_POSEDGE};
  gpio_config(&io_config);

  esp_err_t isr_ret = gpio_install_isr_service(0);
  if (isr_ret != ESP_OK && isr_ret != ESP_ERR_INVALID_STATE)
  {
    ESP_ERROR_CHECK(isr_ret);
  }

  gpio_isr_handler_add(PIN_PIR_MOTION, pir_motion_callback, NULL);
}

/**
 * @brief Read current PIR motion sensor level
 * @return int 0/1 GPIO level for motion sensor
 */
int get_pir_motion_level()
{
  return gpio_get_level(PIN_PIR_MOTION);
}
