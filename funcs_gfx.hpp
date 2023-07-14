#ifndef FUNCS_GFX_HPP
#define FUNCS_GFX_HPP

#include <string>
#include "Point.hpp"

#ifndef SDL_H
#define SDL_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#endif

#pragma once

void update_dir();
void draw_grid(SDL_Renderer*);
void draw_point(SDL_Renderer* , Point&, int, int, SDL_Color);
void render_text(SDL_Renderer*, int, int, const char*, TTF_Font*, SDL_Rect*, SDL_Color&);
void free_ptr();
void load_map(std::string);

#endif