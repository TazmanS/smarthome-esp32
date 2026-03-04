/**
 * @file display_task.h
 * @brief Display task interface
 * @details Declares the FreeRTOS task used to update the LCD display
 */

#ifndef DISPLAY_TASK_H
#define DISPLAY_TASK_H

#include <stdbool.h>
#include "sensors/ir_receiver/ir_receiver.h"

/* ________________________________________ */

typedef enum
{
  SCREEN_COMMON_HOME,
  SCREEN_COMMON_TEMPERATURE,
  SCREEN_COMMON_PHOTOCELL
} display_screen_common_state_t;

typedef enum
{
  SCREEN_MENU_HOME,
  SCREEN_MENU_FAN_MOTOR,
  SCREEN_MENU_DOOR_LED,
  SCREEN_MENU_WINDOW_LED
} display_screen_menu_state_t;

typedef enum
{
  SCREEN_COMMON,
  SCREEN_MENU
} display_screen_type_t;

typedef struct
{
  display_screen_type_t type;
  union
  {
    display_screen_common_state_t common;
    display_screen_menu_state_t menu;
  };
} display_screen_state_t;

/* ________________________________________ */

typedef struct
{
  display_screen_state_t current_state;
} display_config_t;

/* ________________________________________ */

typedef enum
{
  EVENT_SHOW_HOME_SCREEN,
  EVENT_NEXT_COMMON_SCREEN,
  EVENT_PREV_COMMON_SCREEN,
  EVENT_SHOW_MENU_HOME_SCREEN,
  EVENT_NEXT_MENU_SCREEN,
  EVENT_PREV_MENU_SCREEN,

  EVENT_PROCESS_IR_CODE,
  EVENT_TIMER_INTERRUPT
} display_screen_event_t;

/* ________________________________________ */

/**
 * @brief Display task function
 * @details Receives temperature samples and updates the LCD accordingly
 * @param[in] pvParameters Task parameters (unused)
 * @return void
 */
void display_task(void *pvParameters);
void display_event_handler(display_screen_event_t event, ir_button_t code);

#endif