#include "dht.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "DHT";

// Ожидание изменения уровня на пине с таймаутом (µs)
static int32_t wait_for_level(gpio_num_t pin, int level, uint32_t timeout_us)
{
  uint64_t start = esp_timer_get_time();
  while (gpio_get_level(pin) != level)
  {
    if ((esp_timer_get_time() - start) > timeout_us)
      return -1; // таймаут
  }
  return (int32_t)(esp_timer_get_time() - start); // длительность в микросекундах
}

esp_err_t dht_read_data(dht_type_t sensor_type, gpio_num_t pin,
                        float *humidity, float *temperature)
{
  uint8_t data[5] = {0};

  // STEP 1: Start signal
  gpio_set_direction(pin, GPIO_MODE_OUTPUT);
  gpio_set_level(pin, 0);
  vTaskDelay(pdMS_TO_TICKS(20)); // 20 ms

  gpio_set_level(pin, 1);
  esp_rom_delay_us(40); // 20-40 µs

  gpio_set_direction(pin, GPIO_MODE_INPUT);

  // STEP 2: Wait for response LOW/HIGH pulses
  if (wait_for_level(pin, 0, 100) < 0)
  {
    ESP_LOGE(TAG, "No response LOW");
    return ESP_FAIL;
  }
  if (wait_for_level(pin, 1, 100) < 0)
  {
    ESP_LOGE(TAG, "No response HIGH");
    return ESP_FAIL;
  }

  // STEP 3: Read 40 bits
  for (int i = 0; i < 40; i++)
  {
    // wait LOW
    if (wait_for_level(pin, 0, 100) < 0)
      return ESP_FAIL;

    // measure HIGH length
    int32_t high_time = wait_for_level(pin, 1, 100);
    if (high_time < 0)
      return ESP_FAIL;

    // DHT: ~26-28 µs -> 0, ~70 µs -> 1
    if (high_time > 50) // порог между 0 и 1
    {
      data[i / 8] |= (1 << (7 - (i % 8)));
    }
  }

  // STEP 4: Checksum
  uint8_t checksum = data[0] + data[1] + data[2] + data[3];
  if (checksum != data[4])
  {
    ESP_LOGE(TAG, "Checksum error");
    return ESP_FAIL;
  }

  // STEP 5: Parse values
  if (sensor_type == DHT22)
  {
    *humidity = ((data[0] << 8) + data[1]) * 0.1f;
    *temperature = (((data[2] & 0x7F) << 8) + data[3]) * 0.1f;
    if (data[2] & 0x80)
      *temperature = -*temperature;
  }
  else // DHT11
  {
    *humidity = data[0];
    *temperature = data[2];
  }

  return ESP_OK;
}
