/**
 * @file ir_receiver.h
 * @brief Infrared receiver interface
 * @details Provides functions to decode IR remote control signals
 */

#ifndef IR_RECEIVER_H
#define IR_RECEIVER_H

#include "driver/rmt_rx.h"

/**
 * @brief IR remote button codes
 */
typedef enum
{
  IR_CODE_UP = 0x5CA37F80,    /**< Up button */
  IR_CODE_DOWN = 0x750AFF80,  /**< Down button */
  IR_CODE_LEFT = 0x5DA27F80,  /**< Left button */
  IR_CODE_RIGHT = 0x5E21FF80, /**< Right button */
  IR_CODE_OK = 0x5FA07F80,    /**< OK/Enter button */
  IR_CODE_NULL = 0,           /**< No button pressed */
} ir_button_t;

/**
 * @brief Decode IR remote signal
 * @param[in] symbols RMT symbols from receiver
 * @param[in] count Number of symbols
 * @return ir_button_t Decoded button code
 */
ir_button_t ir_get_code(const rmt_symbol_word_t *symbols, size_t count);

/**
 * @brief Convert IR code to string
 * @param[in] code IR button code
 * @return char* String representation of button
 */
char *ir_get_code_to_string(ir_button_t code);

#endif