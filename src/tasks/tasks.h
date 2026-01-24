#pragma once
#include "freertos/FreeRTOS.h"

void tasks_init(void);
extern QueueHandle_t mqttQueue;
extern QueueHandle_t logQueue;

typedef struct
{
  char key[16];
  float value;
  uint32_t timestamp;
} sensor_data_t;
