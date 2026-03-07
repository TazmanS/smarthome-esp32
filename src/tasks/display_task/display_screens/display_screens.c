#include "display_screens.h"
#include "sensors/lcd1602/lcd1602.h"
#include "sensors/leds/leds.h"
#include "sensors/motor/motor.h"

void display_screen_common_home()
{
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("Welcome to");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("SmartHome!");
}

void display_screen_common_temperature(float *temp)
{
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("Temperature:");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("%.1f C   ", *temp);
}

void display_screen_common_photocell(int *photocell)
{
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("PhotoCell:");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("%d   ", *photocell);
}

void display_screen_menu_home()
{
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("SmartHome");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("Menu:");
}

void display_screen_menu_fan_motor()
{
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("Fan Motor");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("Power: %d%%", motor_fan.power);
}

void display_screen_menu_led_door()
{
  char *led_state_str = (led_door.state == LED_ON) ? "ON " : (led_door.state == LED_OFF) ? "OFF"
                                                                                         : "DEF";
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("Door LED");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("Power: %s", led_state_str);
}

void display_screen_menu_led_roof()
{
  char *led_state_str = (led_roof.state == LED_ON) ? "ON " : (led_roof.state == LED_OFF) ? "OFF"
                                                                                         : "DEF";
  lcd1602_set_cursor(0, 0);
  lcd1602_printf("Roof LED");
  lcd1602_set_cursor(0, 1);
  lcd1602_printf("Power: %s", led_state_str);
}
