/**
 * @file pins.c
 * @brief Board pin assignments
 */

#include "pins.h"

const gpio_num_t PIN_LM35 = GPIO_NUM_36;      /**< Analog pin for LM35 temperature sensor */
const gpio_num_t PIN_PHOTOCELL = GPIO_NUM_39; /**< Analog pin for photocell sensor */

const gpio_num_t PIN_I2C_SDA = GPIO_NUM_21; /**< I2C SDA */
const gpio_num_t PIN_I2C_SCL = GPIO_NUM_22; /**< I2C SCL */

const gpio_num_t PIN_LED_DOOR = GPIO_NUM_33; /**< Door LED GPIO */
const gpio_num_t PIN_LED_ROOF = GPIO_NUM_32; /**< Roof LED GPIO */

const gpio_num_t PIN_BUTTON_DOOR = GPIO_NUM_25; /**< Door button GPIO */
const gpio_num_t PIN_BUTTON_ROOF = GPIO_NUM_26; /**< Roof button GPIO */

const gpio_num_t PIN_PIR_MOTION = GPIO_NUM_27; /**< PIR motion sensor GPIO */

const gpio_num_t PIN_SERVO_WINDOW = GPIO_NUM_18;  /**< Window servo GPIO */
const gpio_num_t PIN_MOTOR_FAN_INA = GPIO_NUM_17; /**< Fan motor INA GPIO */
const gpio_num_t PIN_MOTOR_FAN_INB = GPIO_NUM_16; /**< Fan motor INB GPIO */

const gpio_num_t PIN_IR_RECEIVER = GPIO_NUM_5; /**< IR receiver GPIO */
