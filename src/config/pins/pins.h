#ifndef PINS_H
#define PINS_H

#include "driver/gpio.h"

extern const gpio_num_t LM35_PIN;
extern const gpio_num_t I2C_SDA_PIN;
extern const gpio_num_t I2C_SCL_PIN;
extern const gpio_num_t DOOR_LED_PIN;
extern const gpio_num_t ROOF_LED_PIN;

extern const gpio_num_t DOOR_BUTTON_PIN;
extern const gpio_num_t ROOF_BUTTON_PIN;

#endif