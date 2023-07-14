#ifndef GLOBAL_VARS_HPP
#define GLOBAL_VARS_HPP

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#include "Point.hpp"
#pragma once

#define PLAYER_W 10
#define PLAYER_H 10
#define GRID_W 40
#define GRID_H 40
#define WIDTH 680
#define HEIGHT 480
#define STEP_W 10
#define STEP_H 10
#define RED SDL_Color { 255, 0, 0, 0 }
#define GREEN SDL_Color { 0, 255, 0, 0 }
#define YELLOW SDL_Color { 255, 255, 0, 0 }
#define FONT_PATH "C:\\Users\\pierr\\Documents\\Visual Studio 2022\\Projects\\raycasting\\Minecraft.ttf"

/* Variables globales*/

extern SDL_Rect* rect_pos;

extern Point mouse_position;
extern Point target_position;
extern Point dir;

extern char map_array[HEIGHT / GRID_H][WIDTH / GRID_W];

#endif