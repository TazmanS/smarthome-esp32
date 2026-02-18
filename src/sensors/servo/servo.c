/**
 * @file servo.c
 * @brief Servo motor control implementation
 * @details Implements servo angle control using PWM signals
 */

#include "servo.h"
#include "config/pins/pins.h"

Servo window_servo = {};

#define SERVO_MIN_PULSEWIDTH_US 500
#define SERVO_MAX_PULSEWIDTH_US 2500
#define SERVO_MAX_DEGREE 180

static uint32_t servo_per_degree_us =
    (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / SERVO_MAX_DEGREE;

/**
 * @internal
 * @brief Convert angle to PWM duty cycle
 * @param[in] angle Desired angle in degrees
 * @return uint32_t Duty cycle value for LEDC
 */
static uint32_t servo_angle_to_duty(int angle)
{
  uint32_t pulse_width = SERVO_MIN_PULSEWIDTH_US +
                         (servo_per_degree_us * angle);

  uint32_t duty = (pulse_width * ((1 << 16) - 1)) / 20000; // 20ms period
  return duty;
}

/**
 * @brief Initialize servo system
 * @details Sets up the window servo with default pin and channel
 * @return void
 */
void init_servo()
{
  window_servo.gpio_pin = WINDOW_SERVO_PIN;
  window_servo.channel = LEDC_CHANNEL_0;
}

/**
 * @brief Set servo angle
 * @param[in,out] servo Pointer to Servo object
 * @param[in] angle Angle in degrees (0-180)
 * @return void
 */
void set_servo_angle(Servo *servo, int angle)
{
  ledc_set_duty(LEDC_LOW_SPEED_MODE, servo->channel, servo_angle_to_duty(angle));
  ledc_update_duty(LEDC_LOW_SPEED_MODE, servo->channel);
}
