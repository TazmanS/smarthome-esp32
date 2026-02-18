/**
 * @file servo.h
 * @brief Servo motor control interface
 * @details Provides abstraction for controlling servo motors via PWM
 */

#ifndef SERVO_H
#define SERVO_H

#include "driver/ledc.h"

/**
 * @brief Servo object
 */
typedef struct
{
  gpio_num_t gpio_pin;    /**< GPIO pin connected to servo signal */
  ledc_channel_t channel; /**< LEDC channel assigned to servo */
} Servo;

/**
 * @brief Initialize servo system
 * @return void
 */
void init_servo();

/**
 * @brief Set servo angle
 * @param[in,out] servo Pointer to Servo object
 * @param[in] angle Angle in degrees (0-180)
 * @return void
 */
void set_servo_angle(Servo *servo, int angle);

extern Servo window_servo;

#endif