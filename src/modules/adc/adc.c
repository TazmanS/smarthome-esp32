/**
 * @file adc.c
 * @brief ADC (Analog-to-Digital Converter) implementation
 * @details Implements ADC initialization and configuration for analog sensor input
 */

#include "adc.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_adc/adc_cali.h"
#include "esp_adc/adc_cali_scheme.h"
#include "esp_log.h"

/**
 * @brief Initializes ADC hardware
 * @details Configures ADC channels and sampling parameters for sensor readings
 * @return void
 */
void adc_init(ADC_MODULE *adc_module)
{
  adc_oneshot_unit_init_cfg_t adc_unit_conf = {
      .unit_id = adc_module->unit,
  };
  ESP_ERROR_CHECK(adc_oneshot_new_unit(&adc_unit_conf, &(adc_module->adc_handle)));

  adc_oneshot_chan_cfg_t adc_chan_cong = {
      .bitwidth = adc_module->bitwidth,
      .atten = adc_module->attenuation,
  };
  ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_module->adc_handle, adc_module->channel, &adc_chan_cong));
}