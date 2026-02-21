#include "timers.h"
#include "esp_timer.h"
#include "tasks/display_task/display_task.h"

#define SECONDS_5 5000000   // 5 seconds in microseconds
#define SECONDS_60 60000000 // 60 seconds in microseconds
#define SECONDS_15 15000000 // 15 seconds in microseconds

static esp_timer_handle_t motor_on_timer;
static esp_timer_handle_t motor_off_timer;

void motor_off_callback(void *arg)
{
}

void motor_on_callback(void *arg)
{
  // if (motor_running)
  //     return;

  // motor_running = true;
  esp_timer_start_once(motor_off_timer, SECONDS_15);
}

void display_timer_callback(void *arg)
{
  next_display_screen_state();
}

void timers_interrupt_init()
{
  const esp_timer_create_args_t timer_config = {
      .callback = &display_timer_callback,
      .name = "display_timer_interrupt"};

  esp_timer_handle_t timer;
  esp_timer_create(&timer_config, &timer);

  esp_timer_start_periodic(timer, SECONDS_5);

  const esp_timer_create_args_t on_timer_args = {
      .callback = &motor_on_callback,
      .name = "motor_on"};

  const esp_timer_create_args_t off_timer_args = {
      .callback = &motor_off_callback,
      .name = "motor_off"};

  esp_timer_create(&on_timer_args, &motor_on_timer);
  esp_timer_create(&off_timer_args, &motor_off_timer);

  esp_timer_start_periodic(motor_on_timer, SECONDS_60);
}