#include "motor.h"
#include "modules/pwm/pwm.h"
#include "config/pins/pins.h"
#include "config/channels/channels.h"
#include "config/my_timers/my_timers.h"

#define MOTOR_MAX_DUTY 1023

motor_t fan_motor = {};

static void init_motor(motor_t *motor, gpio_num_t pin_INA, gpio_num_t pin_INB, ledc_channel_t channel_INA, ledc_channel_t channel_INB)
{
  motor->pin_INA = pin_INA;
  motor->pin_INB = pin_INB;
  motor->channel_INA = channel_INA;
  motor->channel_INB = channel_INB;
  motor->is_active = false;
  motor->is_reverse = false;
  motor->power = 0;

  gpio_config_t io_conf = {
      .pin_bit_mask = (1ULL << pin_INA) | (1ULL << pin_INB),
      .mode = GPIO_MODE_OUTPUT,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&io_conf);
  gpio_set_level(pin_INA, 0);
  gpio_set_level(pin_INB, 0);

  init_pwm_channel(pin_INA, channel_INA, MOTOR_FAN_TIMER);
  init_pwm_channel(pin_INB, channel_INB, MOTOR_FAN_TIMER);
}

void init_motors()
{
  init_motor(&fan_motor, FAN_MOTOR_INA_PIN, FAN_MOTOR_INB_PIN, FAN_MOTOR_INA_CHANNEL, FAN_MOTOR_INB_CHANNEL);
}

void set_motor_power(motor_t *motor, int power)
{
  if (power < 0)
    power = 0;
  else if (power > 100)
    power = 100;

  motor->power = power;
  uint32_t duty = (MOTOR_MAX_DUTY * motor->power) / 100;

  if (motor->is_reverse)
  {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->channel_INA, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->channel_INA);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->channel_INB, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->channel_INB);
  }
  else
  {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->channel_INA, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->channel_INA);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, motor->channel_INB, duty);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, motor->channel_INB);
  }
}