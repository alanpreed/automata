#include "conway.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static size_t count_neighbours(grid_t *state, int x, int y, bool wrap_edges);
static size_t get_grid_value(grid_t *state, int x, int y, bool wrap_edges);

void conway_step(grid_t *state, bool wrap_edges)
{
  grid_t new_state;
  grid_init(&new_state, state->width, state->height);

  for(size_t j = 0; j < state->height; j++)
  {
    for(size_t i = 0; i < state->width; i++)
    {
      size_t neighbours = count_neighbours(state, i, j, wrap_edges);

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

static size_t get_grid_value(grid_t *state, int x, int y, bool wrap_edges)
{
  size_t xpos, ypos;

  if(!wrap_edges)
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
  else
  {
    if(x < 0)
    {
      xpos = state->width - abs(x % (int)(state->width));
    }
    else if(x >= state->width)
    {
      xpos = x % state->width;
    }
    else
    {
      xpos = x;
    }

    if(y < 0)
    {
      ypos = state->height - abs(y % (int)(state->height));
    }
    else if(y >= state->height)
    {
      ypos = y % state->height;
    }
    else
    {
      ypos = y;
    }
    return state->data[xpos][ypos];
  }
}

static size_t count_neighbours(grid_t *state, int x, int y, bool wrap_edges)
{
  size_t count = 0;
  for(int j = y - 1; j <= y + 1; j++)
  {
    for(int i = x - 1; i <= x + 1; i++)
    {
      if(i != x || j != y)
      {
        if(get_grid_value(state, i, j, wrap_edges) == CONWAY_STATE_ALIVE)
        {
          count++;
        }
      }
    }
  }
  return count;
}