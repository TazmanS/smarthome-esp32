/**
 * @file send_temp.c
 * @brief Temperature sending task implementation
 * @details Implements FreeRTOS task for temperature sensing and MQTT transmission
 */

#include "send_temp_task.h"
#include "tasks/tasks.h"
#include "freertos/FreeRTOS.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_task_wdt.h"
#include <string.h>
#include "tasks/mqtt_task/mqtt_task.h"
#include "tasks/log_task/log_task.h"
#include "sensors/lm35/lm35.h"

#define SEND_TEMP_PERIOD_MS 1000

static const char *TAG = "SendTempTask";

/**
 * @brief Temperature reading and transmission task function
 * @details FreeRTOS task that reads LM35 temperature sensor and sends data via MQTT + Logs + store laste temp
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void send_temp_task(void *pvParameters)
{
  ESP_ERROR_CHECK(esp_task_wdt_add(NULL));

  int64_t max_critical_us = 0;
  uint32_t loops = 0;

  while (1)
  {
    int64_t t0_us = esp_timer_get_time();

    float temp = lm35_read_temperature();

    sensor_data_t data = {
        .timestamp = xTaskGetTickCount()};
    strcpy(data.key, "sensor/temperature");
    data.value = temp;

    xQueueSend(mqtt_queue, &data, portMAX_DELAY);

    xQueueSend(log_queue, &data, portMAX_DELAY);

    xQueueOverwrite(temp_store_queue, &temp);

    int64_t elapsed_us = esp_timer_get_time() - t0_us;
    if (elapsed_us > max_critical_us)
    {
      max_critical_us = elapsed_us;
    }

    loops++;
    if ((loops % 30U) == 0U)
    {
      ESP_LOGI(TAG, "critical(max)=%lld us, temp=%.2f", (long long)max_critical_us, temp);
      max_critical_us = 0;
    }

    esp_task_wdt_reset();

    // TODO take delay from env
    vTaskDelay(pdMS_TO_TICKS(SEND_TEMP_PERIOD_MS));
  }
}
