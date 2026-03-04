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

#define SCREEN_COMMON_COUNT 3
#define SCREEN_MENU_COUNT 4
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
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Welcome to");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("SmartHome!");
    break;

  case SCREEN_COMMON_TEMPERATURE:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Temperature:");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("%.1f C   ", last_temp);
    break;

  case SCREEN_COMMON_PHOTOCELL:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("PhotoCell:");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("%d   ", last_photocell);
    break;

  default:
    break;
  }
}

static void display_menu_screens()
{
  switch (display_config.current_state.menu)
  {
  case SCREEN_MENU_HOME:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("SmartHome");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Menu:");
    break;
  case SCREEN_MENU_FAN_MOTOR:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Fan Motor");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power:");
    break;
  case SCREEN_MENU_DOOR_LED:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Door LED");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power On/Off:");
    break;
  case SCREEN_MENU_WINDOW_LED:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Window LED");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power On/Off:");
    break;

  default:
    break;
  }
}

void display_event_handler(display_screen_event_t event, ir_button_t code)
{
  if (event == EVENT_TIMER_INTERRUPT && display_config.current_state.type == SCREEN_COMMON)
  {
    display_screen_state_t new_state = display_config.current_state;
    new_state.common = (new_state.common + 1) % SCREEN_COMMON_COUNT;
    xQueueOverwrite(display_queue, &new_state);
    return;
  }

  if (event == EVENT_PROCESS_IR_CODE && code == IR_CODE_OK && display_config.current_state.type == SCREEN_COMMON)
  {
    display_screen_state_t new_state = {
        .type = SCREEN_MENU,
        .menu = SCREEN_MENU_HOME};
    xQueueOverwrite(display_queue, &new_state);
    return;
  }

  if (event == EVENT_PROCESS_IR_CODE && display_config.current_state.type == SCREEN_MENU)
  {
    display_screen_state_t new_state = display_config.current_state;

    switch (code)
    {
    case IR_CODE_UP:
      new_state.menu = (new_state.menu - 1 + SCREEN_MENU_COUNT) % SCREEN_MENU_COUNT;
      break;
    case IR_CODE_DOWN:
      new_state.menu = (new_state.menu + 1) % SCREEN_MENU_COUNT;
      break;
    case IR_CODE_OK:
      new_state.type = SCREEN_COMMON;
      new_state.common = SCREEN_COMMON_HOME; // Return to home screen after exiting menu
      break;
    default:
      break;
    }

    xQueueOverwrite(display_queue, &new_state);
    return;
  }
}
