#include "rmt.h"
#include "driver/rmt_rx.h"
#include "esp_log.h"
#include "config/pins/pins.h"
#include "sensors/ir_receiver/ir_receiver.h"
#include "tasks/tasks.h"

static const char *TAG = "RMT_IR_RECEIVER";

#define RMT_BUFFER_SIZE 64

static rmt_symbol_word_t raw_symbols[RMT_BUFFER_SIZE];
static rmt_channel_handle_t rx_chan = NULL;

static const rmt_receive_config_t receive_config = {
    .signal_range_min_ns = 1000,
    .signal_range_max_ns = 12000000};

static bool rmt_rx_done_callback(
    rmt_channel_handle_t channel,
    const rmt_rx_done_event_data_t *edata,
    void *user_ctx)
{
  ir_button_t code = ir_get_code(edata->received_symbols, edata->num_symbols);

  if (code != 0)
  {
    BaseType_t high_task_wakeup = pdFALSE;
    xQueueSendFromISR(ir_queue, &code, &high_task_wakeup);
  }

  rmt_receive(
      channel,
      raw_symbols,
      sizeof(raw_symbols),
      &receive_config);

  return false;
}

void rmt_init()
{
  rmt_rx_channel_config_t rx_chan_config = {
      .clk_src = RMT_CLK_SRC_DEFAULT,
      .gpio_num = IR_RECEIVER_PIN,
      .resolution_hz = 1000000, // 1 tick = 1 us
      .mem_block_symbols = 64};

  ESP_ERROR_CHECK(rmt_new_rx_channel(&rx_chan_config, &rx_chan));

  rmt_rx_event_callbacks_t cbs = {
      .on_recv_done = rmt_rx_done_callback};

  ESP_ERROR_CHECK(rmt_rx_register_event_callbacks(
      rx_chan,
      &cbs,
      NULL));

  ESP_ERROR_CHECK(rmt_enable(rx_chan));

  ESP_LOGI(TAG, "Waiting for IR signals...");

  ESP_ERROR_CHECK(rmt_receive(
      rx_chan,
      raw_symbols,
      sizeof(raw_symbols),
      &receive_config));
}