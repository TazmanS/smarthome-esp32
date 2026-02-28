#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include "driver/rmt_rx.h"

typedef enum
{
  IR_CODE_UP = 0x5CA37F80,
  IR_CODE_DOWN = 0x750AFF80,
  IR_CODE_LEFT = 0x5DA27F80,
  IR_CODE_RIGHT = 0x5E21FF80,
  IR_CODE_OK = 0x5FA07F80
} ir_button_t;

ir_button_t ir_get_code(const rmt_symbol_word_t *symbols, size_t count);
char *ir_get_code_to_string(ir_button_t code);

#endif