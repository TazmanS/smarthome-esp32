#include "lm35.h"
#include "../adc/adc.h"

float lm35_read_temperature()
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

  return voltage_mv / 100.0;
}
