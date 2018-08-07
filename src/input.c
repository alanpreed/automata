#include "input.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static size_t str_to_num(char *argument);

bool input_parse(int argc, char *argv[], input_arguments_t *output)
{
  if(argc < 7)
  {
    printf("Insufficient arguments. Usage:\r\n");
    printf("automata <filename> <model> <number of frames> <scale> <grid width> <grid height>  <model specific options>\r\n");
    return false;
  }

  if(strlen(argv[1]) < INPUT_MAX_STRING_LEN)
  {
    strcpy(output->filename, argv[1]);
  }
  else
  {
    printf("Error: filename too long: %s\r\n", argv[1]);
    return false;
  }

  if(strlen(argv[2]) < INPUT_MAX_STRING_LEN)
  {
    strcpy(output->model, argv[2]);
  }
  else
  {
    printf("Error: model name too long: %s\r\n", argv[2]);
    return false;
  }

  output->num_steps = str_to_num(argv[3]);
  output->scale = str_to_num(argv[4]);
  output->width = str_to_num(argv[5]);
  output->height = str_to_num(argv[6]);

  output->num_model_args = argc - 5;
  for(size_t i = 0; i < output->num_model_args; i++)
  {
    output->model_args[i] = str_to_num(argv[5 + i]);
  }

  return true;
}

static size_t str_to_num(char *argument)
{
  long int value = strtol(argument, NULL, 10);

  if(value <= 0)
  {
    return 0;
  }
  else
  {
    return (size_t)value;
  }
}

