#include "model.h"
#include <stdio.h>
#include <string.h>
#include "conway.h"

#define NUM_MODELS 2

static char *models[NUM_MODELS] = {
  "conway-random",
  "conway-glider",
};

static model_init_t model_init_fns[NUM_MODELS] = {
  conway_setup_random,
  conway_setup_glider,
};

static model_step_t model_step_fns[NUM_MODELS] = {
  conway_step,
  conway_step,
};

static model_convert_t model_convert_fns[NUM_MODELS] = {
  conway_convert,
  conway_convert,
};

static model_free_t model_free_fns[NUM_MODELS] = {
  conway_free,
  conway_free,
};

static size_t model_index;
static bool model_valid = false;
static void *model_state;

bool model_select(char model[])
{
  for(size_t i = 0; i < NUM_MODELS; i++)
  {
    if(strcmp(model, models[i]) == 0)
    {
      model_valid = true;
      model_index = i;
      break;
    }
  }

  if(!model_valid)
  {
    printf("Invalid model choice: %s. Possible options:\r\n", model);
    for(size_t i = 0; i < NUM_MODELS; i++)
    {
      printf("%s\r\n", models[i]);
    }
  }

  return model_valid;
}

bool model_init(int argc, int args[])
{
  if(model_valid)
  {
    return model_init_fns[model_index](&model_state, argc, args);
  }
  else
  {
    return false;
  }
}

void model_step(void)
{
  if(model_valid)
  {
    model_step_fns[model_index](&model_state);
  }
}

void model_convert(uint8_t **data, size_t scale)
{
  if(model_valid)
  {
    model_convert_fns[model_index](model_state, data, scale);
  }
}

void model_free(void)
{
  if(model_valid)
  {
    model_free_fns[model_index](model_state);
  }
}