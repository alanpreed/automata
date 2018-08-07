#include "conway.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static size_t count_neighbours(grid_t *state, int x, int y);
static size_t get_grid_value(grid_t *state, int x, int y);

void conway_step(void **state)
{
  grid_t **state_grid = (grid_t**)state;
  grid_t *new_state;
  grid_init(&new_state, (*state_grid)->width, (*state_grid)->height);

  for(size_t j = 0; j < (*state_grid)->height; j++)
  {
    for(size_t i = 0; i < (*state_grid)->width; i++)
    {
      size_t neighbours = count_neighbours((*state_grid), i, j);

      // Any live cell with fewer than two live neighbors dies, as if by under population.
      // Any live cell with two or three live neighbors lives on to the next generation.
      // Any live cell with more than three live neighbors dies, as if by overpopulation.
      // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
      if((neighbours == 2 &&  (*state_grid)->data[i][j] == CONWAY_STATE_ALIVE) || neighbours == 3)
      {
        new_state->data[i][j] = CONWAY_STATE_ALIVE;
      }
    }
  }
  grid_free(*state_grid);
  *state_grid = new_state;
}

bool conway_setup_glider(void **state, int argc, int args[])
{
  if(argc != 2)
  {
    printf("Warning: wrong number of arguments for Conway glider model (received %d, expected 2)\r\n", argc);
    return false;
  }
  else
  {
    grid_t **state_grid = (grid_t**)state;
    int width = args[0];
    int height = args[1];

    if(width <= 0 || height <= 0)
    {
      printf("Invalid model dimensions: %d x %d\r\n", width, height);
      return false;
    }

    grid_init(state_grid, (size_t)width, (size_t)height);
    (*state_grid)->data[2][0] = CONWAY_STATE_ALIVE;
    (*state_grid)->data[2][1] = CONWAY_STATE_ALIVE;
    (*state_grid)->data[2][2] = CONWAY_STATE_ALIVE;
    (*state_grid)->data[1][2] = CONWAY_STATE_ALIVE;
    (*state_grid)->data[0][1] = CONWAY_STATE_ALIVE;
    return true;
  }
}

bool conway_setup_random(void **state, int argc, int args[])
{
  if(argc != 3)
  {
    printf("Warning: wrong number of arguments for random Conway model (received %d, expected 3)\r\n", argc);
    return false;
  }
  else
  {
    grid_t **state_grid = (grid_t**)state;
    int width = args[0];
    int height = args[1];

    if(width <= 0 || height <= 0)
    {
      printf("Invalid model dimensions: %d x %d\r\n", width, height);
      return false;
    }

    uint8_t probability = args[2];
    grid_init(state_grid, (size_t)width, (size_t)height);

    srand(time(NULL));
    for(size_t j = 0; j < (*state_grid)->height; j++)
    {
      for(size_t i = 0; i < (*state_grid)->width; i++)
      {
        int generated = rand() % 256;

        if(generated <= probability)
        {
          (*state_grid)->data[i][j] = CONWAY_STATE_ALIVE;
        }
      }
    }
    return true;
  }
}

void conway_convert(void *state, uint8_t **data, size_t scale)
{
  grid_t *state_grid = (grid_t*)state;
  *data = calloc(state_grid->width * scale * state_grid->height * scale, sizeof(uint8_t));
  grid_convert(state_grid, *data, scale);
}

void conway_free(void *state)
{
  grid_free((grid_t*)state);
}

static size_t get_grid_value(grid_t *state, int x, int y)
{
  if (x < 0 || y < 0 || x >= state->width || y >= state->height)
  {
    return 0;
  }
  else
  {
    return state->data[x][y];
  }
}

static size_t count_neighbours(grid_t *state, int x, int y)
{
  size_t count = 0;
  for(int j = y - 1; j <= y + 1; j++)
  {
    for(int i = x - 1; i <= x + 1; i++)
    {
      if(i != x || j != y)
      {
        if(get_grid_value(state, i, j) == CONWAY_STATE_ALIVE)
        {
          count++;
        }
      }
    }
  }
  return count;
}