#ifndef INTERRUPTS_TIMERS_H
#define INTERRUPTS_TIMERS_H

void timers_interrupt_init();

void display_timer_off();
void display_timer_on();

void motor_timer_start();
void motor_timer_stop();

#endif