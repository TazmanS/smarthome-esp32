/**
 * @file nvs.h
 * @brief NVS (Non-Volatile Storage) flash helper
 * @details Provides initialization for ESP32 NVS flash storage
 */

#ifndef NVS_H
#define NVS_H

/**
 * @brief Initialize NVS flash
 * @details Initializes or reinitializes NVS if needed
 * @return void
 */
void nvs_init();

#endif