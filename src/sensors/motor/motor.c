#include "motor.h"
#include "modules/pwm/pwm.h"
#include "config/pins/pins.h"
#include "config/channels/channels.h"

motor_t fan_motor = {};

static void init_motor(motor_t *motor, gpio_num_t pin, ledc_channel_t channel)
{
  motor->pin = pin;
  motor->channel = channel;
  motor->is_active = false;

  gpio_config_t io_conf = {
      .intr_type = GPIO_INTR_DISABLE,
      .mode = GPIO_MODE_OUTPUT,
      .pin_bit_mask = (1ULL << pin),
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .pull_up_en = GPIO_PULLUP_DISABLE,
  };
  gpio_config(&io_conf);
  gpio_set_level(motor->pin, 0);

  init_pwm_channel(pin, channel);
}

void init_motors()
{
  init_motor(&fan_motor, FAN_MOTOR_PIN, FAN_MOTOR_CHANNEL);
}