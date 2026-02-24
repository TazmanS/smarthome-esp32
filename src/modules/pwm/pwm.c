/**
 * @file pwm.c
 * @brief PWM implementation for servo control
 * @details Implements PWM timer and channel configuration using ESP32 LEDC
 */

#include "pwm.h"
#include "driver/ledc.h"
#include "esp_err.h"
#include "config/pins/pins.h"
#include "sensors/servo/servo.h"

/**
 * @brief Initialize PWM timer for servo control
 * @details Configures LEDC timer with 50Hz frequency for standard servo operation
 * @return void
 */
void pwm_init_timer()
{
  ledc_timer_config_t timer_servo_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_16_BIT,
      .timer_num = LEDC_TIMER_0,
      .freq_hz = 50,
      .clk_cfg = LEDC_AUTO_CLK,
  };
  ESP_ERROR_CHECK(ledc_timer_config(&timer_servo_config));

  ledc_timer_config_t timer_motor_config = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .duty_resolution = LEDC_TIMER_10_BIT,
      .timer_num = LEDC_TIMER_1,
      .freq_hz = 20000,
      .clk_cfg = LEDC_AUTO_CLK,
  };
  ESP_ERROR_CHECK(ledc_timer_config(&timer_motor_config));
}

/**
 * @brief Initialize PWM channel for a specific servo
 * @param[in,out] servo Pointer to Servo object to configure
 * @return void
 */
void init_pwm_channel(gpio_num_t gpio_pin, ledc_channel_t channel, ledc_timer_t timer)
{
  ledc_channel_config_t channel_config = {
      .gpio_num = gpio_pin,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = channel,
      .intr_type = LEDC_INTR_DISABLE,
      .timer_sel = timer,
      .duty = 0,
      .hpoint = 0};
  ESP_ERROR_CHECK(ledc_channel_config(&channel_config));
}