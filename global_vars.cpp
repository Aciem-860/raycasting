#include "global_vars.hpp"

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif

SDL_Rect* rect_pos = new SDL_Rect();

char map_array[HEIGHT / GRID_H][WIDTH / GRID_W] = { { 0 } };
