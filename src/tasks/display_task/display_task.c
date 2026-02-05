/**
 * @file display_task.c
 * @brief Display task implementation
 * @details Receives stored temperature values and updates the LCD display
 */

#include "display_task.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "tasks/tasks.h"
#include "sensors/lcd1602/lcd1602.h"

/**
 * @brief FreeRTOS task that updates the display with the latest temperature
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters)
{
  while (1)
  {
    float temp;
    if (xQueueReceive(tempStoreQueue, &temp, portMAX_DELAY))
    {
      lcd1602_clear();
      vTaskDelay(pdMS_TO_TICKS(100));
      lcd1602_set_cursor(0, 0);
      lcd1602_printf("Temperature:");

      lcd1602_set_cursor(0, 1);
      lcd1602_printf("%.1f C   ", temp);
    }
  }
}