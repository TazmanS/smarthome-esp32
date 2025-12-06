#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "sensors/lm35/lm35.h"
#include "sensors/wifi/wifi.h"
#include "sensors/mqtt/mqtt.h"

#include "secrets/secrets.h"

#define UART_PORT UART_NUM_1
#define UART_TX_PIN GPIO_NUM_1
#define UART_RX_PIN GPIO_NUM_3

#define UART_BUF_SIZE 1024

void init_uart(void)
{
  uart_config_t uart_config = {
      .baud_rate = 9600,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE};

  uart_param_config(UART_PORT, &uart_config);
  uart_set_pin(UART_PORT, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(UART_PORT, UART_BUF_SIZE, 0, 0, NULL, 0);
}

void app_main(void)
{
  // init_uart();
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

  // uart_write_bytes(UART_PORT, "Hello world!\r\n", 15);

  mqtt_app_start();

  while (1)
  {
    float t = 0;
    lm35_read_temperature(ADC1_CHANNEL_0, &t);

    char buf[64];
    int len = sprintf(buf, "Temperature: %.2f C\r\n", t);
    // uart_write_bytes(UART_PORT, buf, len);

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}
