/**
 * @file display_events.c
 * @brief Display event handling implementation
 * @details Implements event dispatch and state management for display and menu system
 */

#include "display_events.h"
#include "tasks/display_task/display_task.h"
#include "tasks/tasks.h"
#include "sensors/leds/leds.h"
#include "sensors/motor/motor.h"
#include "interrupts/timers/timers.h"

static void event_timer_interrupt_handler(display_config_t *display_config);
static void event_ir_receiver_start_handler(display_config_t *display_config, ir_button_t code);
static void event_ir_receiver_menu_handler(display_config_t *display_config, ir_button_t code);

void display_events_handler(display_event_t event, display_config_t *display_config)
{
  if (event.type == EVENT_TIMER_INTERRUPT && display_config->current_state.type == SCREEN_COMMON)
  {
    // change common screen every timer interrupt
    event_timer_interrupt_handler(display_config);
    return;
  }

  if (event.type == EVENT_PROCESS_IR_CODE && event.ir_receiver.code == IR_CODE_OK && display_config->current_state.type == SCREEN_COMMON)
  {
    // Enter menu on OK button press from common screen
    event_ir_receiver_start_handler(display_config, event.ir_receiver.code);
    motor_timer_stop(); // Stop motor timer when entering menu
    motor_turn_off(&motor_fan);
    return;
  }

  if (event.type == EVENT_PROCESS_IR_CODE && display_config->current_state.type == SCREEN_MENU)
  {
    // Handle menu navigation on IR code press
    event_ir_receiver_menu_handler(display_config, event.ir_receiver.code);
    return;
  }
}

static void event_timer_interrupt_handler(display_config_t *display_config)
{
  display_screen_state_t new_state = display_config->current_state;
  new_state.common = (new_state.common + 1) % SCREEN_COMMON_COUNT;
  xQueueOverwrite(display_queue, &new_state);
}

static void event_ir_receiver_start_handler(display_config_t *display_config, ir_button_t code)
{
  if (code == IR_CODE_OK && display_config->current_state.type == SCREEN_COMMON)
  {
    display_screen_state_t new_state = {
        .type = SCREEN_MENU,
        .menu = SCREEN_MENU_HOME};
    xQueueOverwrite(display_queue, &new_state);
    return;
  }
}

static void event_ir_receiver_menu_handler(display_config_t *display_config, ir_button_t code)
{
  if (display_config->current_state.type != SCREEN_MENU)
  {
    return;
  }

  display_screen_state_t new_state = display_config->current_state;

  switch (code)
  {
  case IR_CODE_UP:
    new_state.menu = (new_state.menu - 1 + SCREEN_MENU_COUNT) % SCREEN_MENU_COUNT;
    break;
  case IR_CODE_DOWN:
    new_state.menu = (new_state.menu + 1) % SCREEN_MENU_COUNT;
    break;
  case IR_CODE_LEFT:
    if (new_state.menu == SCREEN_MENU_FAN_MOTOR)
    {
      motor_set_power(&motor_fan, motor_fan.power - 10);
      motor_turn_on(&motor_fan);
    }
    else if (new_state.menu == SCREEN_MENU_DOOR_LED)
    {
      led_door.state = (led_door.state + 1) % LED_STATE_COUNT;
      if (led_door.state == LED_ON)
      {
        LED_on(&led_door);
      }
      else if (led_door.state == LED_OFF)
      {
        LED_off(&led_door);
      }
    }
    else if (new_state.menu == SCREEN_MENU_ROOF_LED)
    {
      led_roof.state = (led_roof.state + 1) % LED_STATE_COUNT;
      if (led_roof.state == LED_ON)
      {
        LED_on(&led_roof);
      }
      else if (led_roof.state == LED_OFF)
      {
        LED_off(&led_roof);
      }
    }
    break;
  case IR_CODE_RIGHT:
    if (new_state.menu == SCREEN_MENU_FAN_MOTOR)
    {
      motor_set_power(&motor_fan, motor_fan.power + 10);
      motor_turn_on(&motor_fan);
    }
    else if (new_state.menu == SCREEN_MENU_DOOR_LED)
    {
      led_door.state = (led_door.state + 1) % LED_STATE_COUNT;
      if (led_door.state == LED_ON)
      {
        LED_on(&led_door);
      }
      else if (led_door.state == LED_OFF)
      {
        LED_off(&led_door);
      }
    }
    else if (new_state.menu == SCREEN_MENU_ROOF_LED)
    {
      led_roof.state = (led_roof.state + 1) % LED_STATE_COUNT;
      if (led_roof.state == LED_ON)
      {
        LED_on(&led_roof);
      }
      else if (led_roof.state == LED_OFF)
      {
        LED_off(&led_roof);
      }
    }
    break;
  case IR_CODE_OK:
    new_state.type = SCREEN_COMMON;
    new_state.common = SCREEN_COMMON_HOME; // Return to home screen after exiting menu
    motor_timer_start();                   // Restart motor timer when exiting menu
    motor_turn_off(&motor_fan);
    break;
  default:
    break;
  }

  xQueueOverwrite(display_queue, &new_state);
}
