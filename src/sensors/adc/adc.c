#include "adc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "esp_log.h"

#define TAG "ADC"

esp_adc_cal_characteristics_t *adc_chars;
adc1_channel_t ADC_CHANNEL = ADC1_CHANNEL_0;

void adc_init()
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_12);

  adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));

  esp_adc_cal_value_t cal_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, adc_chars); // calibrate

  if (cal_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
    ESP_LOGI(TAG, "Calibrate: eFuse Vref");
  else if (cal_type == ESP_ADC_CAL_VAL_EFUSE_TP)
    ESP_LOGI(TAG, "Calibrate: Two Point");
  else
    ESP_LOGW(TAG, "Calibrate: Default Vref");
}