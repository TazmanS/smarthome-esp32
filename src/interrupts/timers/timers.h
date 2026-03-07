/**
 * @file timers.h
 * @brief Software timer interrupt handlers
 * @details Provides functions for managing periodic timers used by display and motor control
 */

#ifndef INTERRUPTS_TIMERS_H
#define INTERRUPTS_TIMERS_H

/**
 * @brief Initialize timer interrupts
 * @return void
 */
void timers_interrupt_init();

/**
 * @brief Turn off display refresh timer
 * @return void
 */
void display_timer_off();

/**
 * @brief Turn on display refresh timer
 * @return void
 */
void display_timer_on();

/**
 * @brief Start motor control timer cycle
 * @return void
 */
void motor_timer_start();

/**
 * @brief Stop motor control timer cycle
 * @return void
 */
void motor_timer_stop();

#endif