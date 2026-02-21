#include "channels.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

const adc_channel_t LM35_ADC_CHANNEL = ADC_CHANNEL_0;      /** ADC channel for LM35 sensor */
const adc_channel_t PHOTOCELL_ADC_CHANNEL = ADC_CHANNEL_3; /** ADC channel for photocell sensor */

const ledc_channel_t WINDOW_SERVO_CHANNEL = LEDC_CHANNEL_0; /** LEDC channel for window servo control */
const ledc_channel_t FAN_MOTOR_CHANNEL = LEDC_CHANNEL_1;    /** LEDC channel for fan motor control */