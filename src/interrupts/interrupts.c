/**
 * @file interrupts.c
 * @brief Interrupt system initialization implementation
 */

#include "interrupts.h"

#include "interrupts/buttons/buttons.h"
#include "interrupts/timers/timers.h"

void interrupts_init(void)
{
  buttons_interrupt_init();
  timers_interrupt_init();
}