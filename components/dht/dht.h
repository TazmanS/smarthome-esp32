#pragma once

#include "driver/gpio.h"
#include "esp_err.h"

typedef enum
{
  DHT11 = 11,
  DHT22 = 22
} dht_type_t;

esp_err_t dht_read_data(dht_type_t sensor_type, gpio_num_t pin,
                        float *humidity, float *temperature);
