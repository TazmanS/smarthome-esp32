#include "modules.h"

#include "modules/wifi/wifi.h"
#include "modules/mqtt/mqtt.h"
#include "modules/my_i2c/my_i2c.h"
#include "modules/pwm/pwm.h"
#include "modules/adc/adc.h"

#include "config/secrets/secrets.h"

void modules_init()
{
  // wifi_init_sta(WIFI_SSID, WIFI_PASS);
  // mqtt_app_start();
  adc_init();
  i2c_init();
  pwm_init_timer();
}