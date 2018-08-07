#include <stdio.h>
#include <stdlib.h>
#include "gifgen/gifgen.h"
#include "gifgen/colour.h"
#include "model/model.h"
#include "input.h"

#define PALETTE_SIZE 3

colour_t *colours = (colour_t[PALETTE_SIZE]) {
                  (colour_t){0, 0, 0},
                  (colour_t){255, 255, 255},
                  };


input_arguments_t inputs;
uint16_t delay = 10;

// Filename, model, steps, width, height, optional arguments, 
int main(int argc, char *argv[])
{
  printf("Cellula automata gif generator\r\n");

  if(!input_parse(argc, argv, &inputs))
  {
    exit(0);
  }

  printf("Generating %zu x %zu gif with %zu frames\r\n", inputs.width, inputs.height, inputs.num_steps);

  model_select(inputs.model);
  if(!model_init(inputs.num_model_args, inputs.model_args))
  {
    printf("Model initialisation failed\r\n");
    exit(0);
  }
  
  gifgen_start(inputs.filename, inputs.width * inputs.scale, inputs.height * inputs.scale, colours, PALETTE_SIZE);
  
  for(size_t i = 0; i < inputs.num_steps; i++)
  {
    printf("Frame %zu\r\n", i);
    uint8_t *raw_data;
    model_convert(&raw_data, inputs.scale);
    gifgen_add_frame(raw_data, inputs.width * inputs.scale, inputs.height * inputs.scale, delay);
    free(raw_data);
    model_step();
  }

  gifgen_finish();
  model_free();
}


