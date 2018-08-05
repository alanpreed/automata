#ifndef __MODEL_H
#define __MODEL_H

#include <stdbool.h>
#include <stdint.h>

// Interface for implemented models
typedef void (*model_step_t)(void **state);
typedef bool (*model_init_t)(void **state, int argc, int args[]);
typedef void (*model_convert_t)(void *state, uint8_t **data);
typedef void (*model_free_t)(void *state);

bool model_select(char model[]);

bool model_init(int argc, int args[]);
void model_step(void);
void model_convert(uint8_t **data);
void model_free(void);

#endif
