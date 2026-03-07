/**
 * @file ir_task.c
 * @brief Infrared receiver processing task implementation
 */

#include "ir_task.h"
#include "tasks/tasks.h"
#include "tasks/display_task/display_task.h"
#include "sensors/ir_receiver/ir_receiver.h"
#include "esp_log.h"

void ir_task(void *pvParameters)
{
  ir_button_t code;

  while (1)
  {
    if (xQueueReceive(ir_queue, &code, portMAX_DELAY))
    {
      ESP_LOGI("IR TASK", "IR CODE = %s", ir_get_code_to_string(code));
      display_event_t event = {
          .type = EVENT_PROCESS_IR_CODE,
          .ir_receiver = {
              .code = code}};
      display_event_handler(event);
    }
  }
}