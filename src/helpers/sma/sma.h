/**
 * @file sma.h
 * @brief Simple Moving Average (SMA) filter interface
 * @details Provides functions for calculating moving average of sensor readings
 */

#ifndef SMA_H
#define SMA_H

#include <stdint.h>

/**
 * @brief Simple Moving Average filter structure
 */
typedef struct
{
  int *buffer;     /**< Circular buffer for samples */
  int window_size; /**< Number of samples in the window */
  int index;       /**< Current index in circular buffer */
  int count;       /**< Current count of samples */
  int sum;         /**< Sum of all samples in window */
} sma_filter_t;

/**
 * @brief Initialize SMA filter
 * @param[out] filter Pointer to filter structure
 * @param[in] buffer Preallocated buffer for samples
 * @param[in] window_size Number of samples to average
 * @return void
 */
void sma_init(sma_filter_t *filter, int *buffer, int window_size);

/**
 * @brief Add a sample to the filter
 * @param[in,out] filter Pointer to filter structure
 * @param[in] sample New sample value
 * @return int Moving average of current window
 */
int sma_add_sample(sma_filter_t *filter, int sample);

#endif
