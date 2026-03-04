#include "timers.h"
#include "esp_timer.h"
#include "tasks/display_task/display_task.h"
#include "sensors/motor/motor.h"

#define SECONDS_5 5000000   // 5 seconds in microseconds
#define SECONDS_60 60000000 // 60 seconds in microseconds
#define SECONDS_15 15000000 // 15 seconds in microseconds

#define DISPLAY_TIMER_PERIOD SECONDS_5

static esp_timer_handle_t motor_on_timer;
static esp_timer_handle_t motor_off_timer;
static esp_timer_handle_t display_timer;

void motor_off_callback(void *arg)
{
  fan_motor.is_active = false;
  set_motor_power(&fan_motor, 0);
}

void motor_on_callback(void *arg)
{
  if (fan_motor.is_active)
    return;

  fan_motor.is_active = true;
  set_motor_power(&fan_motor, 100);
  esp_timer_start_once(motor_off_timer, SECONDS_5);
}

void display_timer_callback(void *arg)
{
  display_event_handler(EVENT_TIMER_INTERRUPT, IR_CODE_NULL);
}

void display_timer_off()
{
  esp_timer_stop(display_timer);
}

void display_timer_on()
{
  esp_timer_start_periodic(display_timer, DISPLAY_TIMER_PERIOD);
}

void timers_interrupt_init()
{
  // DISPLAY
  const esp_timer_create_args_t timer_config = {
      .callback = &display_timer_callback,
      .name = "display_timer_interrupt"};

  esp_timer_create(&timer_config, &display_timer);

  esp_timer_start_periodic(display_timer, DISPLAY_TIMER_PERIOD);

  // MOTORS
  const esp_timer_create_args_t on_timer_args = {
      .callback = &motor_on_callback,
      .name = "motor_on"};

  const esp_timer_create_args_t off_timer_args = {
      .callback = &motor_off_callback,
      .name = "motor_off"};

  esp_timer_create(&on_timer_args, &motor_on_timer);
  esp_timer_create(&off_timer_args, &motor_off_timer);

  esp_timer_start_periodic(motor_on_timer, SECONDS_15);
}