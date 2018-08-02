#include <stdio.h>
#include "grid.h"
#include "gifgen/gifgen.h"
#include "gifgen/colour.h"
#include "model/conway.h"

#define PALETTE_SIZE 3

colour_t *colours = (colour_t[PALETTE_SIZE]) {
                  (colour_t){0, 0, 0},
                  (colour_t){255, 255, 255},
                  };

grid_t conway_game;
size_t width = 300;
size_t height = 300;
size_t num_steps = 100;
uint16_t delay = 10;

int main(int argc, char *argv[])
{
  printf("Cellula Automata\r\n");

  printf("Generating %zu x %zu gif with %zu frames\r\n", width, height, num_steps);

  grid_init(&conway_game, width, height);

  //conway_setup_glider(&conway_game);
  conway_setup_random(&conway_game, 5);

  char filename[15] = "conway.gif";

  gifgen_start(filename, width, height, colours, PALETTE_SIZE);
  
  for(size_t i = 0; i < num_steps; i++)
  {
    printf("Frame %zu\r\n", i);
    uint8_t raw_data[width * height];
    grid_convert(&conway_game, raw_data);
    gifgen_add_frame(raw_data, width, height, delay);
    conway_step(&conway_game);
  }

  gifgen_finish();

  grid_free(&conway_game);
}
