#ifndef SMA_H
#define SMA_H

#include <stdint.h>

typedef struct
{
  int *buffer;
  int window_size;
  int index;
  int count;
  int sum;
} sma_filter_t;

void sma_init(sma_filter_t *filter, int *buffer, int window_size);
int sma_add_sample(sma_filter_t *filter, int sample);

#endif
