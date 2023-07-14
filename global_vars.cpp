#include "global_vars.hpp"

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#endif

SDL_Rect* rect_pos = new SDL_Rect();
Point mouse_position = Point(0, 0);
Point target_position = Point(375, 230);
Point dir = target_position - mouse_position;

char map_array[HEIGHT / GRID_H][WIDTH / GRID_W] = { { 0 } };
