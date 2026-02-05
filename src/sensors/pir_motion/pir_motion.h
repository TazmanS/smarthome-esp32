/**
 * @file pir_motion.h
 * @brief PIR motion sensor interface
 * @details Provides initialization and API to read PIR motion sensor state
 */

#ifndef PIR_MOTION_H
#define PIR_MOTION_H

/**
 * @brief Initialize PIR motion sensor interrupt
 * @return void
 */
void pir_motion_init();

/**
 * @brief Read current PIR motion sensor level
 * @return int 0/1 GPIO level for motion sensor
 */
int get_pir_motion_level();

#endif