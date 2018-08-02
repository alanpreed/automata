#include "conway.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_neighbours(grid_t *state, int x, int y);
static size_t get_grid_value(grid_t *state, int x, int y);

void conway_step(grid_t *state)
{
  grid_t new_state;
  grid_init(&new_state, state->width, state->height);

  for(size_t j = 0; j < state->height; j++)
  {
    for(size_t i = 0; i < state->width; i++)
    {
      size_t neighbours = count_neighbours(state, i, j);

      // Any live cell with fewer than two live neighbors dies, as if by under population.
      // Any live cell with two or three live neighbors lives on to the next generation.
      // Any live cell with more than three live neighbors dies, as if by overpopulation.
      // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
      if((neighbours == 2 &&  state->data[i][j] == CONWAY_STATE_ALIVE) || neighbours == 3)
      {
        new_state.data[i][j] = CONWAY_STATE_ALIVE;
      }
    }
  }
  grid_free(state);
  *state = new_state;
}

void conway_setup_glider(grid_t *state)
{
  state->data[2][0] = CONWAY_STATE_ALIVE;
  state->data[2][1] = CONWAY_STATE_ALIVE;
  state->data[2][2] = CONWAY_STATE_ALIVE;
  state->data[1][2] = CONWAY_STATE_ALIVE;
  state->data[0][1] = CONWAY_STATE_ALIVE;
}

void conway_setup_random(grid_t *state, uint8_t probability)
{
  for(size_t j = 0; j < state->height; j++)
  {
    for(size_t i = 0; i < state->width; i++)
    {
      int generated = rand() % 256;

      if(generated <= probability)
      {
        state->data[i][j] = CONWAY_STATE_ALIVE;
      }
    }
  }
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