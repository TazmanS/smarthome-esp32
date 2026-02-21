/**
 * @file lm35.c
 * @brief LM35 temperature sensor implementation
 * @details Implements temperature reading and conversion for LM35 analog sensor
 */

#include "lm35.h"
#include "config/pins/pins.h"
#include "config/channels/channels.h"
#include "modules/adc/adc.h"
#include "helpers/sma/sma.h"

#define ADC_MAX_RAW 4095.0
#define ADC_MAX_MV 3300.0

#define SMA_WINDOW_SIZE 16
static int sma_buffer[SMA_WINDOW_SIZE];
static sma_filter_t lm35_sma;

adc_module_t adc_lm35_module = {};

void init_lm35()
{
  adc_lm35_module.pin = LM35_PIN,
  adc_lm35_module.channel = LM35_ADC_CHANNEL,
  adc_lm35_module.attenuation = ADC_ATTEN_DB_12,
  adc_lm35_module.bitwidth = ADC_BITWIDTH_12,
  adc_init_channel(&adc_lm35_module);

  sma_init(&lm35_sma, sma_buffer, SMA_WINDOW_SIZE);
};

/**
 * @brief Reads temperature from LM35 sensor
 * @details Performs ADC conversion and converts raw value to Celsius
 * @return float Temperature value in Celsius
 */
float lm35_read_temperature(void)
{
  int raw_adc_value = 0;
  ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, adc_lm35_module.channel, &raw_adc_value));
  float voltage_mv = ((float)raw_adc_value / ADC_MAX_RAW) * ADC_MAX_MV;
  int averaged_mv = sma_add_sample(&lm35_sma, (int)voltage_mv);
  float temperature_c = averaged_mv / 10.0f;
  return temperature_c;
}
