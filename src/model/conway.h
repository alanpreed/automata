#ifndef __CONWAY_H
#define __CONWAY_H

#include "../grid.h"
#include <stdbool.h>

#define CONWAY_STATE_ALIVE 1
#define CONWAY_STATE_DEAD 0

void conway_step(grid_t *state);

void conway_setup_glider(grid_t *state);
void conway_setup_random(grid_t *state, uint8_t probability);

#endif
