#include "channels.h"
#include "esp_adc/adc_oneshot.h"
#include "driver/ledc.h"

const adc_channel_t CHANNEL_ADC_LM35 = ADC_CHANNEL_0;      /** ADC channel for LM35 sensor */
const adc_channel_t CHANNEL_ADC_PHOTOCELL = ADC_CHANNEL_3; /** ADC channel for photocell sensor */

const ledc_channel_t CHANNEL_SERVO_WINDOW = LEDC_CHANNEL_0;  /** LEDC channel for window servo control */
const ledc_channel_t CHANNEL_MOTOR_FAN_INA = LEDC_CHANNEL_1; /** LEDC channel for fan motor INA control */
const ledc_channel_t CHANNEL_MOTOR_FAN_INB = LEDC_CHANNEL_2; /** LEDC channel for fan motor INB control */