#include <stdio.h>
#include "grid.h"
#include "gifgen.h"
#include "lzw.h"

grid_t test_grid;

int main(int argc, char *argv[])
{
  printf("Cellula Automata\r\n");

  // grid_init(&test_grid, 5, 5);

  // grid_print(&test_grid);

  // for(size_t i = 0; i < test_grid.width; i++)
  // {
  //   test_grid.data[i][3] = 1;
  //   grid_print(&test_grid);
  // }

  char filename[10] = "test3.gif";
  
  
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

  grid_free(&test_grid);

}
