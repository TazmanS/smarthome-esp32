/**
 * @file lm35.c
 * @brief LM35 temperature sensor implementation
 * @details Implements temperature reading and conversion for LM35 analog sensor
 */

#include "lm35.h"
#include "../adc/adc.h"

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

  return voltage_mv / 10.0;
}
