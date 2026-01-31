#ifndef LCD1602_H
#define LCD1602_H

#include "driver/i2c.h"
#include <stdint.h>

void lcd1602_init(i2c_port_t i2c_port);
void lcd1602_clear(void);
void lcd1602_set_cursor(uint8_t col, uint8_t row);
void lcd1602_print(const char *str);
void lcd1602_printf(const char *fmt, ...);

#endif