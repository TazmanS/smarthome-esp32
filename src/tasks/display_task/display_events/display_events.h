/**
 * @file display_events.h
 * @brief Display event handling interface
 * @details Declares event handler for display navigation and menu control
 */

#ifndef DISPLAY_EVENTS_H
#define DISPLAY_EVENTS_H

#include "tasks/display_task/display_task.h"

/**
 * @brief Handle display events (timer, IR remote)
 * @param[in] event Display event to process
 * @param[in,out] display_config Display configuration state
 * @return void
 */
void display_events_handler(display_event_t event, display_config_t *display_config);

#endif