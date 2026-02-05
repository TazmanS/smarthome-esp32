/**
 * @file my_i2c.c
 * @brief I2C helper implementation
 * @details Implements initialization of I2C master used by LCD and other I2C peripherals
 */

#include "my_i2c.h"
#include "driver/i2c.h"
#include "config/pins/pins.h"

/**
 * @brief Initialize I2C peripheral
 * @details Configures and installs the I2C master driver on I2C_NUM_0
 * @return void
 */
void i2c_init(void)
{
  i2c_config_t config = {
      .mode = I2C_MODE_MASTER,
      .sda_io_num = I2C_SDA_PIN,
      .scl_io_num = I2C_SCL_PIN,
      .sda_pullup_en = GPIO_PULLUP_ENABLE,
      .scl_pullup_en = GPIO_PULLUP_ENABLE,
      .master.clk_speed = 100000,
  };

  i2c_param_config(I2C_NUM_0, &config);
  i2c_driver_install(I2C_NUM_0, config.mode, 0, 0, 0);
}