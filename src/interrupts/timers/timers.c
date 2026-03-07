#include "timers.h"
#include "esp_timer.h"
#include "tasks/display_task/display_task.h"
#include "sensors/motor/motor.h"

#define SECONDS_5 5000000   // 5 seconds in microseconds
#define SECONDS_60 60000000 // 60 seconds in microseconds
#define SECONDS_15 15000000 // 15 seconds in microseconds

#define MOTOR_RUN_TIME SECONDS_5
#define MOTOR_PERIOD_TIME SECONDS_15

#define DISPLAY_TIMER_PERIOD SECONDS_5

static esp_timer_handle_t motor_on_timer;
static esp_timer_handle_t motor_off_timer;
static esp_timer_handle_t display_timer;

void motor_off_callback(void *arg)
{
  motor_fan.is_active = false;
  motor_turn_off(&motor_fan);
}

void motor_on_callback(void *arg)
{
  if (motor_fan.is_active)
    return;

  motor_fan.is_active = true;
  motor_turn_on(&motor_fan);
  esp_timer_start_once(motor_off_timer, MOTOR_RUN_TIME);
}

void motor_timer_stop()
{
  esp_timer_stop(motor_on_timer);
  esp_timer_stop(motor_off_timer);
}

void motor_timer_start()
{
  esp_timer_start_periodic(motor_on_timer, MOTOR_PERIOD_TIME);
}

void display_timer_callback(void *arg)
{
  display_event_t event = {.type = EVENT_TIMER_INTERRUPT};
  display_event_handler(event);
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

  esp_timer_start_periodic(motor_on_timer, MOTOR_PERIOD_TIME);
}