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
#include "sensors/ir_receiver/ir_receiver.h"
#include "display_screens/display_screens.h"
#include "display_events/display_events.h"

#define CLEAR_TIMER 100

static void display_common_screens();
static void display_menu_screens();

static display_config_t display_config = {
    .current_state = {
        .type = SCREEN_COMMON,
        .common = SCREEN_COMMON_HOME}};

/**
 * @brief FreeRTOS task that updates the display with the latest temperature
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters)
{
  lcd1602_clear();
  vTaskDelay(pdMS_TO_TICKS(CLEAR_TIMER));

  display_screen_state_t new_state;

  while (1)
  {
    if (xQueueReceive(display_queue, &new_state, 0))
    {
      display_config.current_state = new_state;
      lcd1602_clear();
      vTaskDelay(pdMS_TO_TICKS(CLEAR_TIMER));
    }

    if (display_config.current_state.type == SCREEN_COMMON)
    {
      display_common_screens();
    }
    else
    {
      display_menu_screens();
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void display_common_screens()
{
  float temp;
  int photocell;
  static float last_temp = 0.0f;
  static int last_photocell = 0;

  if (xQueueReceive(temp_store_queue, &temp, 0))
  {
    last_temp = temp;
  }

  if (xQueueReceive(photo_cell_store_queue, &photocell, 0))
  {
    last_photocell = photocell;
  }

  switch (display_config.current_state.common)
  {
  case SCREEN_COMMON_HOME:
    display_screen_common_home();
    break;

  case SCREEN_COMMON_TEMPERATURE:
    display_screen_common_temperature(&last_temp);
    break;

  case SCREEN_COMMON_PHOTOCELL:
    display_screen_common_photocell(&last_photocell);
    break;

  default:
    break;
  }
}

static void display_menu_screens()
{
  // need queue to get LED state
  switch (display_config.current_state.menu)
  {
  case SCREEN_MENU_HOME:
    display_screen_menu_home();
    break;
  case SCREEN_MENU_FAN_MOTOR:
    display_screen_menu_fan_motor();
    break;
  case SCREEN_MENU_DOOR_LED:
    display_screen_menu_led_door();
    break;
  case SCREEN_MENU_ROOF_LED:
    display_screen_menu_led_roof();
    break;

  default:
    break;
  }
}

void display_event_handler(display_event_t event)
{
  display_events_handler(event, &display_config);
}
