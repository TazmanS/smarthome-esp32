/**
 * @file photocell.h
 * @brief Photocell (light sensor) interface
 * @details Provides functions to initialize and read light levels from photocell sensor
 */

#ifndef PHOTOCELL_H
#define PHOTOCELL_H

/**
 * @brief Initialize photocell sensor
 * @return void
 */
void photocell_init();

/**
 * @brief Read light level from photocell
 * @details Returns the analog light level reading
 * @return int Light level value (0-4095 for 12-bit ADC)
 */
int photocell_read_light_level();

#endif