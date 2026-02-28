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
#include "sensors/photocell/photocell.h"

static DisplayScreenState currentState = DISPLAY_GREETINGS;
static DisplayScreenState newState;

/**
 * @brief FreeRTOS task that updates the display with the latest temperature
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters)
{
  lcd1602_clear();
  vTaskDelay(pdMS_TO_TICKS(100));

  float temp;
  int photocell;

  while (1)
  {
    xQueueReceive(temp_store_queue, &temp, portMAX_DELAY);
    xQueueReceive(photo_cell_store_queue, &photocell, portMAX_DELAY);

    if (xQueueReceive(display_queue, &newState, 0))
    {
      currentState = newState;
      lcd1602_clear();
      vTaskDelay(pdMS_TO_TICKS(100));
    }

    switch (currentState)
    {
    case DISPLAY_GREETINGS:
      lcd1602_set_cursor(0, 0);
      lcd1602_printf("Welcome to");
      lcd1602_set_cursor(0, 1);
      lcd1602_printf("SmartHome!");
      break;

    case DISPLAY_TEMPERATURE:
      lcd1602_set_cursor(0, 0);
      lcd1602_printf("Temperature:");
      lcd1602_set_cursor(0, 1);
      lcd1602_printf("%.1f C   ", temp);
      break;

    case DISPLAY_PHOTOCELL:
      lcd1602_set_cursor(0, 0);
      lcd1602_printf("PhotoCell:");
      lcd1602_set_cursor(0, 1);
      lcd1602_printf("%d   ", photocell);
      break;

    default:
      break;
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

void set_display_screen_state(DisplayScreenState newState)
{
  if (display_queue != NULL)
  {
    xQueueOverwrite(display_queue, &newState);
  }
}

void next_display_screen_state()
{
  newState = (currentState + 1) % 3;
  xQueueOverwrite(display_queue, &newState);
}