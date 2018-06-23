#include <stdlib.h>
#include <stdio.h>
#include "grid.h"

void grid_init(grid_t *grid, size_t width, size_t height)
{
  grid->width = width;
  grid->height = height;
  grid->data = calloc(grid->width, sizeof(size_t*));

  for(size_t i = 0; i < grid->height; i++)
  {
    grid->data[i] = calloc(grid->height, sizeof(size_t));
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

void grid_free(grid_t *grid)
{
  for(size_t i = 0; i < grid->height; i++)
  {
    free(grid->data[i]);
  }
  free(grid->data);
}
