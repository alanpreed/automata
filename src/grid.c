#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

void grid_init(grid_t **grid, size_t width, size_t height)
{
  *grid = calloc(1, sizeof(grid_t));
  (*grid)->width = width;
  (*grid)->height = height;
  (*grid)->data = calloc((*grid)->width, sizeof(size_t*));

  for(size_t i = 0; i < (*grid)->width; i++)
  {
    (*grid)->data[i] = calloc((*grid)->height, sizeof(size_t));
  }
}

void grid_print(grid_t *grid)
{
  for(size_t j = 0; j < grid->height; j++)
  {
    for(size_t i = 0; i < grid->width; i++)
    {
      printf("%zu ", grid->data[i][j]);
    }
    printf("\r\n");
  }
  printf("\r\n");
}

void grid_convert(grid_t *grid, uint8_t *raw, size_t scale)
{
  for(size_t j = 0; j < grid->height * scale; j++)
  {
    for(size_t i = 0; i < grid->width * scale; i++)
    {
      raw[i + (j * grid->width * scale)] = (uint8_t)grid->data[i / scale][j / scale];
    }
  }
}

void grid_free(grid_t *grid)
{
  for(size_t i = 0; i < grid->width; i++)
  {
    free(grid->data[i]);
  }
  free(grid->data);
  free(grid);
}
