#include "nvs_flash.h"

#include "sensors/wifi/wifi.h"
#include "sensors/mqtt/mqtt.h"
#include "sensors/adc/adc.h"

#include "secrets/secrets.h"
#include "tasks/tasks.h"

void app_main(void)
{
  adc_init();

  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  wifi_init_sta(WIFI_SSID, WIFI_PASS);

  mqtt_app_start();

  tasks_init();
}
