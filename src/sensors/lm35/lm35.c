/**
 * @file lm35.c
 * @brief LM35 temperature sensor implementation
 * @details Implements temperature reading and conversion for LM35 analog sensor
 */

#include "lm35.h"
#include "modules/adc/adc.h"

#define SMA_WINDOW_SIZE 16

static int sma_buffer[SMA_WINDOW_SIZE];
static int sma_index = 0;
static int sma_count = 0;
static int sma_sum = 0;

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
  const int samples = 32;
  uint32_t sum = 0;

  for (int i = 0; i < samples; i++)
  {
    sum += adc1_get_raw(ADC_CHANNEL);
    for (volatile int i = 0; i < 1000; i++)
      ;
  }

  uint32_t raw = sum / samples;
  uint32_t voltage_mv = esp_adc_cal_raw_to_voltage(raw, adc_chars);

  uint32_t smoothed_voltage = sma_add_sample(voltage_mv);

  return smoothed_voltage / 10.0;
}
