#ifndef __CONWAY_H
#define __CONWAY_H

#include "../grid.h"
#include <stdbool.h>

#define CONWAY_STATE_ALIVE 1
#define CONWAY_STATE_DEAD 0

void conway_step(void **state);

bool conway_setup_glider(void **state, int argc, int args[]);
bool conway_setup_random(void **state, int argc, int args[]);
void conway_convert(void *state, uint8_t **data);
void conway_free(void *state);

#endif
