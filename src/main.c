#include <stdio.h>
#include "grid.h"
#include "gifgen/gifgen.h"
#include "gifgen/colour.h"

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

  uint8_t input_colour_indices_2[100] = { 
                                        1,1,1,0,0,0,0,2,2,2,
                                        1,1,1,0,0,0,0,2,2,2,
                                        2,2,2,0,0,0,0,1,1,1,
                                        2,2,2,0,0,0,0,1,1,1,
                                        1,1,1,1,1,2,2,2,2,2,
                                        1,1,1,1,1,2,2,2,2,2,
                                        1,1,1,1,1,2,2,2,2,2,
                                        2,2,2,2,2,1,1,1,1,1,
                                        2,2,2,2,2,1,1,1,1,1,
                                        2,2,2,2,2,1,1,1,1,1,
                                      };

  #define PALETTE_SIZE 10

  colour_t *colours = (colour_t[PALETTE_SIZE]) {
                    (colour_t){226, 35, 216},
                    (colour_t){74, 75, 211},
                    (colour_t){220, 43, 91},
                    (colour_t){123, 166, 27},
                    (colour_t){252, 180, 12},
                    (colour_t){111, 75, 235},
                    (colour_t){159, 16, 66},
                    (colour_t){215, 27, 37},
                    (colour_t){0, 0, 0},
                    (colour_t){255, 255, 255},
                    };

  gifgen_start(filename, 10, 10, colours, PALETTE_SIZE);

  gifgen_add_frame(input_colour_indices, 10, 10, 50);
  gifgen_add_frame(input_colour_indices_2, 10, 10, 50);

  gifgen_finish();

  char filename2[15] = "second.gif";

  gifgen_start(filename2, 5, 5, colours, PALETTE_SIZE);

  gifgen_add_frame(raw_data, 5, 5, 500);

  gifgen_finish();

  grid_free(&test_grid);
}
