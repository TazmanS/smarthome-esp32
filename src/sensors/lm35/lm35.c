/**
 * @file lm35.c
 * @brief LM35 temperature sensor implementation
 * @details Implements temperature reading and conversion for LM35 analog sensor
 */

#include "lm35.h"
#include "config/pins/pins.h"
#include "modules/adc/adc.h"

#define SMA_WINDOW_SIZE 16
#define ADC_MAX_RAW 4095.0
#define ADC_MAX_MV 3300.0

static int sma_buffer[SMA_WINDOW_SIZE];
static int sma_index = 0;
static int sma_count = 0;
static int sma_sum = 0;

ADC_MODULE adc_lm35_module = {};

void init_lm35()
{
  adc_lm35_module.pin = LM35_PIN,
  adc_lm35_module.channel = ADC_CHANNEL_0,
  adc_lm35_module.unit = ADC_UNIT_1,
  adc_lm35_module.attenuation = ADC_ATTEN_DB_12,
  adc_lm35_module.bitwidth = ADC_BITWIDTH_12,
  adc_init(&adc_lm35_module);
};

static int sma_add_sample(int new_sample)
{
  if (sma_count == SMA_WINDOW_SIZE)
  {
    sma_sum -= sma_buffer[sma_index];
  }
  else
  {
    sma_count++;
  }

  sma_buffer[sma_index] = new_sample;
  sma_sum += new_sample;

  sma_index++;
  if (sma_index >= SMA_WINDOW_SIZE)
  {
    sma_index = 0;
  }

  return sma_sum / sma_count;
}

/**
 * @brief Reads temperature from LM35 sensor
 * @details Performs ADC conversion and converts raw value to Celsius
 * @return float Temperature value in Celsius
 */
float lm35_read_temperature(void)
{
  int raw_adc_value = 0;
  ESP_ERROR_CHECK(adc_oneshot_read(adc_lm35_module.adc_handle, adc_lm35_module.channel, &raw_adc_value));
  float voltage_mv = ((float)raw_adc_value / ADC_MAX_RAW) * ADC_MAX_MV;
  float averaged_mv = sma_add_sample((int)voltage_mv);
  float temperature_c = averaged_mv / 10.0f;
  return temperature_c;
}
