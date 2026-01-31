#include "lcd1602.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include "esp_rom_sys.h"

#define LCD_ADDR 0x27
#define LCD_BACKLIGHT 0x08
#define ENABLE 0x04
#define RS 0x01

static i2c_port_t lcd_i2c_port;

static void lcd_write(uint8_t data)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, (LCD_ADDR << 1) | I2C_MASTER_WRITE, true);
  i2c_master_write_byte(cmd, data | LCD_BACKLIGHT, true);
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(lcd_i2c_port, cmd, pdMS_TO_TICKS(50));
  i2c_cmd_link_delete(cmd);
}

static void lcd_pulse(uint8_t data)
{
  lcd_write(data | ENABLE);
  esp_rom_delay_us(5);
  lcd_write(data & ~ENABLE);
  esp_rom_delay_us(100);
}

static void lcd_write4(uint8_t data)
{
  uint8_t out = (data & 0xF0) | (data & (RS | LCD_BACKLIGHT));
  lcd_write(out);
  lcd_pulse(out);
}

static void lcd_send(uint8_t value, uint8_t mode)
{
  uint8_t high = (value & 0xF0) | mode;
  uint8_t low = ((value << 4) & 0xF0) | mode;

  lcd_write4(high);
  vTaskDelay(pdMS_TO_TICKS(1));
  lcd_write4(low);
  vTaskDelay(pdMS_TO_TICKS(1));
}

static void lcd_cmd(uint8_t cmd)
{
  lcd_send(cmd, 0);
}

static void lcd_data(uint8_t data)
{
  lcd_send(data, RS);
}

void lcd1602_init(i2c_port_t i2c_port)
{
  lcd_i2c_port = i2c_port;

  vTaskDelay(pdMS_TO_TICKS(100));

  lcd_write4(0x30);
  vTaskDelay(pdMS_TO_TICKS(10));
  lcd_write4(0x30);
  vTaskDelay(pdMS_TO_TICKS(10));
  lcd_write4(0x30);
  vTaskDelay(pdMS_TO_TICKS(10));
  lcd_write4(0x20);

  lcd_cmd(0x28); // 4-bit, 2 lines
  lcd_cmd(0x0C); // display ON
  lcd_cmd(0x06); // cursor move
  lcd_cmd(0x01); // clear

  vTaskDelay(pdMS_TO_TICKS(5));
}

void lcd1602_clear(void)
{
  lcd_cmd(0x01);
  vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd1602_set_cursor(uint8_t col, uint8_t row)
{
  static uint8_t row_offsets[] = {0x00, 0x40};
  lcd_cmd(0x80 | (col + row_offsets[row]));
}

void lcd1602_print(const char *str)
{
  while (*str)
  {
    lcd_data((uint8_t)*str++);
  }
}

void lcd1602_printf(const char *fmt, ...)
{
  char buf[32];
  va_list args;
  va_start(args, fmt);
  vsnprintf(buf, sizeof(buf), fmt, args);
  va_end(args);
  lcd1602_print(buf);
}
