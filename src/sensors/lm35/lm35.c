#include "lm35.h"
#include "esp_log.h"

static const char *TAG = "LM35";

esp_err_t lm35_init(adc1_channel_t channel)
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(channel, ADC_ATTEN_DB_6);

  ESP_LOGI(TAG, "LM35 init done");
  return ESP_OK;
}

esp_err_t lm35_read_temperature(adc1_channel_t channel, float *temperature)
{
  int raw = adc1_get_raw(channel);
  if (raw < 0)
    return ESP_FAIL;

  float voltage = ((float)raw / 4095.0f) * 2200.0f;
  *temperature = voltage / 10.0f;

  // ESP_LOGI(TAG, "raw=%d mv=%.1f temp=%.1f", raw, voltage, *temperature);
  return ESP_OK;
}
