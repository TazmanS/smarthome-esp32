/**
 * @file ir_receiver.c
 * @brief Infrared receiver implementation
 * @details Implements NEC protocol decoding and button code recognition
 */

#include "ir_receiver.h"
#include "driver/rmt_rx.h"

/**
 * @internal
 * @brief Decode NEC IR protocol
 * @param[in] symbols RMT symbols from receiver
 * @param[in] count Number of symbols
 * @return uint32_t Decoded IR code
 */
uint32_t decode_nec(const rmt_symbol_word_t *symbols, size_t count)
{
  if (count < 34)
    return 0;

  uint32_t code = 0;

  for (int i = 0; i < 32; i++)
  {
    const rmt_symbol_word_t *s = &symbols[i + 2];

    if (s->duration1 > 1000)
      code |= (1U << i);
  }

  return code;
}

ir_button_t ir_get_code(const rmt_symbol_word_t *symbols, size_t count)
{
  uint32_t code = decode_nec(symbols, count);

  switch (code)
  {
  case IR_CODE_UP:
    return IR_CODE_UP;
  case IR_CODE_DOWN:
    return IR_CODE_DOWN;
  case IR_CODE_LEFT:
    return IR_CODE_LEFT;
  case IR_CODE_RIGHT:
    return IR_CODE_RIGHT;
  case IR_CODE_OK:
    return IR_CODE_OK;
  default:
    return 0;
  }
}

char *ir_get_code_to_string(ir_button_t code)
{
  switch (code)
  {
  case IR_CODE_UP:
    return "UP";
  case IR_CODE_DOWN:
    return "DOWN";
  case IR_CODE_LEFT:
    return "LEFT";
  case IR_CODE_RIGHT:
    return "RIGHT";
  case IR_CODE_OK:
    return "OK";
  default:
    return "UNKNOWN";
  }
}