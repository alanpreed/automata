#include "colour_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

bool colour_table_init(colour_t *colours, size_t size, colour_table_t *table)
{
  // Size of colour table encoded in gif is 2^(N+1), where N is the colour table size value
  table->N = ceil((log((double)size) / log(2.0)) - 1.0);
  table->size = pow(2, table->N + 1);

  table->colours = calloc(table->size, sizeof(colour_t));

  if(table->colours == NULL)
  {
    return true;
  }
  else
  {
    memcpy(table->colours, colours, sizeof(colour_t) * size);
    return false;
  }
}

size_t colour_table_convert(colour_table_t *table, uint8_t **bytes)
{
  size_t final_table_size = pow(2, table->N + 1);

  if(table->size != final_table_size)
  {
    printf("Warning: colour table is not a valid length!\r\n");
  }

  *bytes = calloc(final_table_size * 3, sizeof(uint8_t));

  for(size_t i = 0; i < table->size; i++)
  {
    (*bytes)[(3 * i)] = table->colours[i].red;
    (*bytes)[(3 * i) + 1] = table->colours[i].green;
    (*bytes)[(3 * i) + 2] = table->colours[i].blue;
  }

  return table->size * 3;
}

void colour_table_free(colour_table_t *table)
{
  free(table->colours);
}