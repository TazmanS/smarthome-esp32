/**
 * @file display_task.h
 * @brief Display task interface
 * @details Declares the FreeRTOS task used to update the LCD display
 */

#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#include <stdbool.h>
#include "sensors/ir_receiver/ir_receiver.h"

typedef enum
{
  DISPLAY_GREETINGS,
  DISPLAY_TEMPERATURE,
  DISPLAY_PHOTOCELL
} display_screen_state_t;

typedef enum
{
  MAIN_MENU,
  FAN_MOTOR_MENU,
  DOOR_LED_MENU,
  WINDOW_LED_MENU
} display_menu_state_t;

typedef void (*menu_action_t)(void);

typedef struct
{
  ir_button_t code;
  display_menu_state_t menu_state;
  menu_action_t action_left;
  menu_action_t action_right;
} display_menu_item_t;

typedef struct
{
  display_screen_state_t current_state;
  display_menu_state_t current_menu_state;
  bool is_menu_open;
} display_config_t;

// typedef enum
// {
//   DISPLAY_EVENT_SCREEN,
//   DISPLAY_EVENT_MENU
// } display_event_type_t;

// typedef struct
// {
//   display_event_type_t type;
//   union
//   {
//     display_screen_state_t screen;
//     display_menu_state_t menu;
//   };
// } display_event_t;

/**
 * @brief Display task function
 * @details Receives temperature samples and updates the LCD accordingly
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters);
void next_display_screen_state();
void display_process_code(ir_button_t code);

#endif