/**
 * @file pins.h
 * @brief Board pin mapping
 * @details Defines symbolic names for GPIOs used across the project
 */

#ifndef PINS_H
#define PINS_H

#include "driver/gpio.h"

extern const gpio_num_t LM35_PIN;      /** LM35 analog sensor pin */
extern const gpio_num_t PHOTOCELL_PIN; /** Photocell analog sensor pin */

extern const gpio_num_t I2C_SDA_PIN; /** I2C SDA pin */
extern const gpio_num_t I2C_SCL_PIN; /** I2C SCL pin */

extern const gpio_num_t DOOR_LED_PIN; /** Door LED pin */
extern const gpio_num_t ROOF_LED_PIN; /** Roof LED pin */

extern const gpio_num_t DOOR_BUTTON_PIN; /** Door button pin */
extern const gpio_num_t ROOF_BUTTON_PIN; /** Roof button pin */

extern const gpio_num_t PIR_MOTION_PIN; /** PIR motion sensor pin */

extern const gpio_num_t WINDOW_SERVO_PIN; /** Window servo pin */
extern const gpio_num_t FAN_MOTOR_PIN;    /** Fan motor pin */

#endif