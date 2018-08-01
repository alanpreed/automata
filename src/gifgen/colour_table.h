#ifndef __COLOUR_TABLE_H
#define __COLOUR_TABLE_H
#include "colour.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct {
  colour_t *colours;
  size_t size;
  uint8_t N;
} colour_table_t;

bool colour_table_init(colour_t *colours, size_t size, colour_table_t *table);

size_t colour_table_convert(colour_table_t *table, uint8_t **bytes);

void colour_table_free(colour_table_t *table);

#endif
