#include "pwm.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "config/pins/pins.h"
#include "sensors/servo/servo.h"

#define SERVO_PWM_FREQ 50
#define SERVO_PWM_RESOLUTION LEDC_TIMER_16_BIT

void init_pwm_timer()
{
  ledc_timer_config_t timer_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = SERVO_PWM_RESOLUTION,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = SERVO_PWM_FREQ,
      .clk_cfg = LEDC_AUTO_CLK,
  };
  ESP_ERROR_CHECK(ledc_timer_config(&timer_config));
}

void init_pwm_channel(Servo *servo)
{
  ledc_channel_config_t channel_config = {
      .gpio_num = servo->gpio_pin,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = servo->channel,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = LEDC_TIMER_0,
      .duty = 0,
      .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&channel_config));
}