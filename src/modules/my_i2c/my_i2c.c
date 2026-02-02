#include "my_i2c.h"
#include "driver/i2c.h"
#include "config/pins/pins.h"

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