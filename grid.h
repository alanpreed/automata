#ifndef __GRID_H
#define __GRID_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  size_t width;
  size_t height;
  size_t **data;
} grid_t;

void grid_init(grid_t *grid, size_t width, size_t height);

void grid_print(grid_t *grid);

void grid_free(grid_t *grid);

#endif