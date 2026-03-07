/**
 * @file sma.c
 * @brief Simple Moving Average filter implementation
 */

#include "sma.h"

/**
 * @brief Initialize SMA filter
 * @param[out] filter Pointer to filter structure
 * @param[in] buffer Preallocated buffer for samples
 * @param[in] window_size Number of samples to average
 * @return void
 */
void sma_init(sma_filter_t *filter, int *buffer, int window_size)
{
  filter->buffer = buffer;
  filter->window_size = window_size;
  filter->index = 0;
  filter->count = 0;
  filter->sum = 0;

  for (int i = 0; i < window_size; i++)
  {
    buffer[i] = 0;
  }
}

/**
 * @brief Add a sample to the filter
 * @param[in,out] filter Pointer to filter structure
 * @param[in] sample New sample value
 * @return int Moving average of current window
 */
int sma_add_sample(sma_filter_t *filter, int sample)
{
  if (filter->count == filter->window_size)
  {
    filter->sum -= filter->buffer[filter->index];
  }
  else
  {
    filter->count++;
  }

  filter->buffer[filter->index] = sample;
  filter->sum += sample;

  filter->index++;
  if (filter->index >= filter->window_size)
  {
    filter->index = 0;
  }

  return filter->sum / filter->count;
}
