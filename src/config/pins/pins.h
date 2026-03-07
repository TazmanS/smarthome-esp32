/**
 * @file pins.h
 * @brief Board pin mapping
 * @details Defines symbolic names for GPIOs used across the project
 */

#ifndef PINS_H
#define PINS_H

#include "driver/gpio.h"

extern const gpio_num_t PIN_LM35;      /** LM35 analog sensor pin */
extern const gpio_num_t PIN_PHOTOCELL; /** Photocell analog sensor pin */

extern const gpio_num_t PIN_I2C_SDA; /** I2C SDA pin */
extern const gpio_num_t PIN_I2C_SCL; /** I2C SCL pin */

extern const gpio_num_t PIN_LED_DOOR; /** Door LED pin */
extern const gpio_num_t PIN_LED_ROOF; /** Roof LED pin */

extern const gpio_num_t PIN_BUTTON_DOOR; /** Door button pin */
extern const gpio_num_t PIN_BUTTON_ROOF; /** Roof button pin */

extern const gpio_num_t PIN_PIR_MOTION; /** PIR motion sensor pin */

extern const gpio_num_t PIN_SERVO_WINDOW;  /** Window servo pin */
extern const gpio_num_t PIN_MOTOR_FAN_INA; /**< Fan motor INA GPIO */
extern const gpio_num_t PIN_MOTOR_FAN_INB; /**< Fan motor INB GPIO */

extern const gpio_num_t PIN_IR_RECEIVER; /**< IR receiver GPIO */

#endif