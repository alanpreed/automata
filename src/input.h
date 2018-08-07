#ifndef __INPUT_H
#define __INPUT_H

#include <stddef.h>
#include <stdbool.h>

#define INPUT_MAX_STRING_LEN 20
#define INPUT_MAX_ARGS 10

typedef struct{
  char filename[INPUT_MAX_STRING_LEN];
  char model[INPUT_MAX_STRING_LEN];
  size_t num_steps;
  size_t width;
  size_t height;
  size_t scale;
  int num_model_args;
  int model_args[INPUT_MAX_ARGS];
} input_arguments_t;

bool input_parse(int argc, char *argv[], input_arguments_t *output);

#endif