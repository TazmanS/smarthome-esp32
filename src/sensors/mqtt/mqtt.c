#include "mqtt.h"
#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "MQTT";

void mqtt_app_start(void)
{
  esp_mqtt_client_config_t mqtt_cfg = {
      .broker.address.hostname = "192.168.31.210",
      .broker.address.port = 1883,
  };

  esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
  esp_mqtt_client_start(client);

  esp_mqtt_client_publish(client, "sensor/temperature", "25.4", 0, 1, 0);

  ESP_LOGI(TAG, "Message published to broker");
}
