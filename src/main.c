#include <stdio.h>
#include "grid.h"
#include "gifgen/gifgen.h"
#include "gifgen/colour.h"
#include "conway.h"

#define PALETTE_SIZE 3

colour_t *colours = (colour_t[PALETTE_SIZE]) {
                  (colour_t){0, 0, 0},
                  (colour_t){255, 255, 255},
                  };
grid_t conway_game;
size_t width = 20;
size_t height = 20;
size_t num_steps = 100;
uint16_t delay = 10;

int main(int argc, char *argv[])
{
  printf("Cellula Automata\r\n");

  grid_init(&conway_game, width, height);

  conway_game.data[2][0] = CONWAY_STATE_ALIVE;
  conway_game.data[2][1] = CONWAY_STATE_ALIVE;
  conway_game.data[2][2] = CONWAY_STATE_ALIVE;
  conway_game.data[1][2] = CONWAY_STATE_ALIVE;
  conway_game.data[0][1] = CONWAY_STATE_ALIVE;

  grid_print(&conway_game);

  char filename[15] = "conway.gif";

  gifgen_start(filename, width, height, colours, PALETTE_SIZE);
  
  for(size_t i = 0; i < num_steps; i++)
  {
    uint8_t raw_data[width * height];
    grid_convert(&conway_game, raw_data);
    gifgen_add_frame(raw_data, width, height, delay);
    conway_step(&conway_game, true);
  }

  gifgen_finish();

  grid_free(&conway_game);
}
