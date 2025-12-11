#include "lm35.h"
#include "esp_adc_cal.h"

static esp_adc_cal_characteristics_t *adc_chars;

void lm35_init(adc1_channel_t channel)
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(channel, ADC_ATTEN_DB_12);

  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));

  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, adc_chars);
}

float lm35_read_temperature(adc1_channel_t channel)
{
  int raw = adc1_get_raw(channel);
  uint32_t voltage = esp_adc_cal_raw_to_voltage(raw, adc_chars);
  float temp = voltage / 100.0f;
  return temp;
}
