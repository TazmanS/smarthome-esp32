/**
 * @file photocell.c
 * @brief Photocell sensor implementation
 * @details Implements photocell sensor reading with SMA filtering
 */

#include "photocell.h"
#include "modules/adc/adc.h"
#include "config/pins/pins.h"
#include "config/channels/channels.h"
#include "helpers/sma/sma.h"
#include "esp_log.h"

adc_module_t photocell_adc_module = {};

#define SMA_WINDOW_SIZE 16
static int sma_buffer[SMA_WINDOW_SIZE];
static sma_filter_t photocell_sma;
static const char *TAG = "PHOTOCELL";

void photocell_init()
{
  photocell_adc_module.pin = PIN_PHOTOCELL,
  photocell_adc_module.channel = CHANNEL_ADC_PHOTOCELL,
  photocell_adc_module.attenuation = ADC_ATTEN_DB_12,
  photocell_adc_module.bitwidth = ADC_BITWIDTH_12,
  adc_init_channel(&photocell_adc_module);

  sma_init(&photocell_sma, sma_buffer, SMA_WINDOW_SIZE);
}

int photocell_read_light_level()
{
  static int last_valid_value = 0;

  int raw_adc_value = 0;
  esp_err_t err = adc_oneshot_read(adc_handle, photocell_adc_module.channel, &raw_adc_value);
  if (err != ESP_OK)
  {
    ESP_LOGW(TAG, "adc_oneshot_read failed: %s", esp_err_to_name(err));
    return last_valid_value;
  }

  if (raw_adc_value < 0)
  {
    raw_adc_value = 0;
  }
  else if (raw_adc_value > 4095)
  {
    raw_adc_value = 4095;
  }

  int averaged_value = sma_add_sample(&photocell_sma, raw_adc_value);
  last_valid_value = averaged_value;
  return averaged_value;
}