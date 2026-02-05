/**
 * @file pins.c
 * @brief Board pin assignments
 */

#include "pins.h"

const gpio_num_t LM35_PIN = GPIO_NUM_4;      /**< Analog pin for LM35 temperature sensor */
const gpio_num_t I2C_SDA_PIN = GPIO_NUM_21;  /**< I2C SDA */
const gpio_num_t I2C_SCL_PIN = GPIO_NUM_22;  /**< I2C SCL */
const gpio_num_t DOOR_LED_PIN = GPIO_NUM_33; /**< Door LED GPIO */
const gpio_num_t ROOF_LED_PIN = GPIO_NUM_32; /**< Roof LED GPIO */

const gpio_num_t DOOR_BUTTON_PIN = GPIO_NUM_25; /**< Door button GPIO */
const gpio_num_t ROOF_BUTTON_PIN = GPIO_NUM_26; /**< Roof button GPIO */

const gpio_num_t PIR_MOTION_PIN = GPIO_NUM_27; /**< PIR motion sensor GPIO */
;