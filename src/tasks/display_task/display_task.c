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

#define MENU_ITEMS_COUNT 4

void display_menu_execute_action_left();
void display_menu_execute_action_right();
static void display_render();
static void display_render_menu();

static const display_menu_item_t menu_items[MENU_ITEMS_COUNT] = {
    {IR_CODE_UP, MAIN_MENU, NULL, NULL},
    {IR_CODE_DOWN, FAN_MOTOR_MENU, NULL, NULL},
    {IR_CODE_OK, DOOR_LED_MENU, display_menu_execute_action_left, display_menu_execute_action_right},
    {IR_CODE_UP, WINDOW_LED_MENU, display_menu_execute_action_left, display_menu_execute_action_right},
};

static display_config_t display_config = {
    .current_state = DISPLAY_GREETINGS,
    .current_menu_state = MAIN_MENU,
    .is_menu_open = false};

/**
 * @brief FreeRTOS task that updates the display with the latest temperature
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters)
{
  lcd1602_clear();
  vTaskDelay(pdMS_TO_TICKS(100));

  while (1)
  {
    if (display_config.is_menu_open)
    {
      display_render_menu();
    }
    else
    {
      display_render();
    }

    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}

static void display_render()
{
  float temp;
  int photocell;
  static float last_temp = 0.0f;
  static int last_photocell = 0;

  display_screen_state_t new_state;

  if (xQueueReceive(temp_store_queue, &temp, 0))
  {
    last_temp = temp;
  }

  if (xQueueReceive(photo_cell_store_queue, &photocell, 0))
  {
    last_photocell = photocell;
  }

  if (xQueueReceive(display_queue, &new_state, 0))
  {
    display_config.current_state = new_state;
    lcd1602_clear();
    vTaskDelay(pdMS_TO_TICKS(100));
  }

  switch (display_config.current_state)
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
    lcd1602_printf("%.1f C   ", last_temp);
    break;

  case DISPLAY_PHOTOCELL:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("PhotoCell:");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("%d   ", last_photocell);
    break;

  default:
    break;
  }
}

static void display_render_menu()
{
  switch (display_config.current_menu_state)
  {
  case MAIN_MENU:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("SmartHome");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Menu:");
    break;
  case FAN_MOTOR_MENU:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Fan Motor");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power:");
    break;
  case DOOR_LED_MENU:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Door LED");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power On/Off:");
    break;
  case WINDOW_LED_MENU:
    lcd1602_set_cursor(0, 0);
    lcd1602_printf("Window LED");
    lcd1602_set_cursor(0, 1);
    lcd1602_printf("Power On/Off:");
    break;

  default:
    break;
  }
}

void set_display_screen_state(display_screen_state_t new_state)
{
  if (display_queue != NULL)
  {
    xQueueOverwrite(display_queue, &new_state);
  }
}

void next_display_screen_state()
{
  display_screen_state_t new_state = (display_config.current_state + 1) % 3;
  xQueueOverwrite(display_queue, &new_state);
}

void display_menu_on()
{
  lcd1602_clear();
  display_config.is_menu_open = true;
  display_config.current_menu_state = menu_items[0].menu_state;
}

void display_menu_off()
{
  display_config.is_menu_open = false;
  display_config.current_state = DISPLAY_GREETINGS;
}

void display_menu_next_item()
{
  if (display_config.is_menu_open)
  {
    display_menu_state_t next_state = ((display_config.current_menu_state + 1) % MENU_ITEMS_COUNT);
    display_config.current_menu_state = next_state;
  }
}

void display_menu_previous_item()
{
  if (display_config.is_menu_open)
  {
    display_menu_state_t previous_state = (display_config.current_menu_state - 1 + MENU_ITEMS_COUNT) % MENU_ITEMS_COUNT;
    display_config.current_menu_state = previous_state;
  }
}

void display_menu_execute_action_left() {}

void display_menu_execute_action_right() {}

void display_process_code(ir_button_t code)
{
  if (!display_config.is_menu_open && code == IR_CODE_OK)
  {
    display_menu_on();
    return;
  }

  if (display_config.is_menu_open)
  {
    lcd1602_clear();
    switch (code)
    {
    case IR_CODE_UP:
      display_menu_previous_item();
      break;

    case IR_CODE_DOWN:
      display_menu_next_item();
      break;

    case IR_CODE_OK:
      display_menu_off();
      break;

    default:
      break;
    }
  }
}
