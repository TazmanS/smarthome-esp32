#include "timers.h"
#include "esp_timer.h"
#include "tasks/display_task/display_task.h"

#define SECONDS_5 5000000 // 5 seconds in microseconds

void timer_callback(void *arg)
{
  next_display_screen_state();
}

void timers_interrupt_init()
{
  const esp_timer_create_args_t timer_config = {
      .callback = &timer_callback,
      .name = "timer_interrupt"};

  esp_timer_handle_t timer;
  esp_timer_create(&timer_config, &timer);

  esp_timer_start_periodic(timer, SECONDS_5);
}