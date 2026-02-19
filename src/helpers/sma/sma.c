#include "sma.h"

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
