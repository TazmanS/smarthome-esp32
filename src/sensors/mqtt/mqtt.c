/**
 * @file mqtt.c
 * @brief MQTT client implementation
 * @details Implements MQTT client initialization and message handling
 */

#include "mqtt.h"
#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "MQTT";

static esp_mqtt_client_handle_t client = NULL;

void mqtt_publish(const char *topic, const char *data)
{
  if (client == NULL)
  {
    ESP_LOGE(TAG, "MQTT client not initialized!");
    return;
  }

  int msg_id = esp_mqtt_client_publish(client, topic, data, 0, 1, 0);

  if (msg_id >= 0)
  {
    ESP_LOGI(TAG, "Published to %s: %s", topic, data);
  }
  else
  {
    ESP_LOGE(TAG, "Failed to publish message");
  }
}

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data)
{
  esp_mqtt_event_handle_t event = event_data;

  switch (event->event_id)
  {

  case MQTT_EVENT_CONNECTED:
    ESP_LOGI(TAG, "MQTT CONNECTED");
    break;

  case MQTT_EVENT_DISCONNECTED:
    ESP_LOGW(TAG, "MQTT DISCONNECTED");
    break;

  case MQTT_EVENT_ERROR:
    ESP_LOGE(TAG, "MQTT ERROR");
    break;

  case MQTT_EVENT_DATA:
    ESP_LOGI(TAG, "DATA RECEIVED");
    printf("Topic: %.*s\n", event->topic_len, event->topic);
    printf("Data:  %.*s\n", event->data_len, event->data);
    break;

  default:
    ESP_LOGI(TAG, "Other event id:%d", event->event_id);
    break;
  }
}

/**
 * @brief Starts MQTT client application
 * @details Initializes and connects MQTT client to broker for IoT communication
 * @return void
 */
void mqtt_app_start(void)
{
  esp_mqtt_client_config_t mqtt_cfg = {
      .broker.address.uri = "mqtt://192.168.31.210:1883",
  };

  client = esp_mqtt_client_init(&mqtt_cfg);

  esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);

  esp_mqtt_client_start(client);
}
