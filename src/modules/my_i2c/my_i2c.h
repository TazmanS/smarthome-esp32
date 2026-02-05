/**
 * @file my_i2c.h
 * @brief I2C helper interface
 * @details Declares initialization function for I2C peripherals used by sensors and display
 */

#ifndef MY_I2C_H
#define MY_I2C_H

/**
 * @brief Initialize I2C peripheral
 * @details Configures I2C master interface and installs driver for the project
 * @return void
 */
void i2c_init(void);

#endif