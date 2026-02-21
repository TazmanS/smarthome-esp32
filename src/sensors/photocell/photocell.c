#include "photocell.h"
#include "modules/adc/adc.h"
#include "config/pins/pins.h"
#include "config/channels/channels.h"
#include "helpers/sma/sma.h"

adc_module_t photocell_adc_module = {};

#define SMA_WINDOW_SIZE 16
static int sma_buffer[SMA_WINDOW_SIZE];
static sma_filter_t photocell_sma;

void init_photocell()
{
  photocell_adc_module.pin = PHOTOCELL_PIN,
  photocell_adc_module.channel = PHOTOCELL_ADC_CHANNEL,
  photocell_adc_module.attenuation = ADC_ATTEN_DB_12,
  photocell_adc_module.bitwidth = ADC_BITWIDTH_12,
  adc_init_channel(&photocell_adc_module);

  sma_init(&photocell_sma, sma_buffer, SMA_WINDOW_SIZE);
}

int photocell_read_light_level()
{
  int raw_adc_value = 0;
  ESP_ERROR_CHECK(adc_oneshot_read(adc_handle, photocell_adc_module.channel, &raw_adc_value));
  int averaged_value = sma_add_sample(&photocell_sma, raw_adc_value);
  return averaged_value;
}