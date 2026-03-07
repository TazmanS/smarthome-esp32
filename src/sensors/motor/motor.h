/**
 * @file motor.h
 * @brief DC motor control interface
 * @details Provides motor abstraction for controlling fans and other DC motors
 */

#ifndef MOTOR_H
#define MOTOR_H

#include "driver/gpio.h"
#include "driver/ledc.h"

/**
 * @brief DC motor structure
 */
typedef struct
{
  gpio_num_t pin_INA;         /**< GPIO pin for motor input A */
  gpio_num_t pin_INB;         /**< GPIO pin for motor input B */
  ledc_channel_t channel_INA; /**< LEDC channel for INA PWM */
  ledc_channel_t channel_INB; /**< LEDC channel for INB PWM */
  bool is_active;             /**< Motor active state */
  bool is_reverse;            /**< Motor direction (forward/reverse) */
  int power;                  /**< Motor power level (0-100) */
} motor_t;

/** @brief Global fan motor instance */
extern motor_t motor_fan;

/**
 * @brief Initialize motor system
 * @return void
 */
void motors_init();

/**
 * @brief Set motor power level
 * @param[in,out] motor Pointer to motor structure
 * @param[in] power Power level (0-100)
 * @return void
 */
void motor_set_power(motor_t *motor, int power);

/**
 * @brief Turn motor off
 * @param[in,out] motor Pointer to motor structure
 * @return void
 */
void motor_turn_off(motor_t *motor);

/**
 * @brief Turn motor on
 * @param[in,out] motor Pointer to motor structure
 * @return void
 */
void motor_turn_on(motor_t *motor);

#endif