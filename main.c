#include <stdio.h>
#include "grid.h"

grid_t test_grid;

int main(int argc, char *argv[])
{
  printf("Cellula Automata\r\n");

  grid_init(&test_grid, 5, 5);

  grid_print(&test_grid);

  for(size_t i = 0; i < test_grid.width; i++)
  {
    test_grid.data[i][3] = 1;
    grid_print(&test_grid);
  }

  grid_free(&test_grid);
}
