#ifndef DISPLAY_SCREENS_H
#define DISPLAY_SCREENS_H

void display_screen_common_home();
void display_screen_common_temperature(float *temp);
void display_screen_common_photocell(int *photocell);

void display_screen_menu_home();
void display_screen_menu_fan_motor();
void display_screen_menu_led_door();
void display_screen_menu_led_roof();

#endif