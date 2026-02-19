#include "channels.h"
#include "esp_adc/adc_oneshot.h"

const adc_channel_t LM35_ADC_CHANNEL = ADC_CHANNEL_0;      /** ADC channel for LM35 sensor */
const adc_channel_t PHOTOCELL_ADC_CHANNEL = ADC_CHANNEL_3; /** ADC channel for photocell sensor */