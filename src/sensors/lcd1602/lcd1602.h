/**
 * @file lcd1602.h
 * @brief HD44780 over I2C helper API
 * @details Functions to initialize and print to an I2C-connected 16x2 LCD
 */

#ifndef LCD1602_H
#define LCD1602_H

#include "driver/i2c.h"
#include <stdint.h>

/**
 * @brief Initialize LCD driver
 * @param[in] i2c_port I2C port used for the LCD
 * @return void
 */
void lcd1602_init(i2c_port_t i2c_port);
/**
 * @brief Clear LCD display
 * @return void
 */
void lcd1602_clear(void);
/**
 * @brief Set cursor position
 * @param[in] col Column (0-based)
 * @param[in] row Row (0-based)
 * @return void
 */
void lcd1602_set_cursor(uint8_t col, uint8_t row);
/**
 * @brief Print a string to the LCD at the current cursor position
 * @param[in] str Null-terminated string
 * @return void
 */
void lcd1602_print(const char *str);
/**
 * @brief Print formatted text to the LCD
 * @param[in] fmt printf-style format
 * @return void
 */
void lcd1602_printf(const char *fmt, ...);

#endif