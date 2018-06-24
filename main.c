#include <stdio.h>
#include "grid.h"
#include "gifgen/gifgen.h"

grid_t test_grid;

int main(int argc, char *argv[])
{
  printf("Cellula Automata\r\n");

  uint8_t raw_data[25];

  grid_init(&test_grid, 5, 5);

  grid_print(&test_grid);

  grid_convert(&test_grid, raw_data);

  for(size_t i = 0; i < 25; i++)
  {
    printf("%u ", raw_data[i]);
  }
  printf("\r\n");

  test_grid.data[2][3] = 1;

    grid_print(&test_grid);

  grid_convert(&test_grid, raw_data);

  for(size_t i = 0; i < 25; i++)
  {
    printf("%u ", raw_data[i]);
  }
  printf("\r\n");


  char filename[15] = "test.gif";
  
  uint8_t input_colour_indices[100] = { 1,1,1,1,1,2,2,2,2,2,
                                        1,1,1,1,1,2,2,2,2,2,
                                        1,1,1,1,1,2,2,2,2,2,
                                        1,1,1,0,0,0,0,2,2,2,
                                        1,1,1,0,0,0,0,2,2,2,
                                        2,2,2,0,0,0,0,1,1,1,
                                        2,2,2,0,0,0,0,1,1,1,
                                        2,2,2,2,2,1,1,1,1,1,
                                        2,2,2,2,2,1,1,1,1,1,
                                        2,2,2,2,2,1,1,1,1,1,
                                      };

  gifgen_start(filename, 10, 10);

  gifgen_add_frame(input_colour_indices, 10, 10);

  gifgen_finish();

  char filename2[15] = "second.gif";

  gifgen_start(filename2, 5, 5);

  gifgen_add_frame(raw_data, 5, 5);

  gifgen_finish();

  grid_free(&test_grid);

}
