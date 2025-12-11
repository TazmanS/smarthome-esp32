#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "sensors/lm35/lm35.h"
#include "sensors/wifi/wifi.h"
#include "sensors/mqtt/mqtt.h"

#include "secrets/secrets.h"

void app_main(void)
{
  lm35_init(ADC1_CHANNEL_0);

  ESP_LOGI("MAIN", "Initializing NVS...");
  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);
  wifi_init_sta(WIFI_SSID, WIFI_PASS);

  mqtt_app_start();

  while (1)
  {
    float t = lm35_read_temperature(ADC1_CHANNEL_0);

    char buf[64];
    sprintf(buf, "{\"temperature\": %.2f}", t);

    mqtt_publish("sensor/temperature", buf);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
