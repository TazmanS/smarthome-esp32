/**
 * @file display_screens.h
 * @brief LCD display screen rendering functions
 * @details Provides functions to render different screens on the 16x2 LCD display
 */

#ifndef DISPLAY_SCREENS_H
#define DISPLAY_SCREENS_H

/**
 * @brief Display common home screen
 * @return void
 */
void display_screen_common_home();

/**
 * @brief Display temperature reading screen
 * @param[in] temp Pointer to current temperature value
 * @return void
 */
void display_screen_common_temperature(float *temp);

/**
 * @brief Display photocell light level screen
 * @param[in] photocell Pointer to light level reading
 * @return void
 */
void display_screen_common_photocell(int *photocell);

/**
 * @brief Display menu home screen
 * @return void
 */
void display_screen_menu_home();

/**
 * @brief Display fan motor control menu
 * @return void
 */
void display_screen_menu_fan_motor();

/**
 * @brief Display door LED control menu
 * @return void
 */
void display_screen_menu_led_door();

/**
 * @brief Display roof LED control menu
 * @return void
 */
void display_screen_menu_led_roof();

#endif