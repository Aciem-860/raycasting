#ifndef FUNCS_GFX_HPP
#define FUNCS_GFX_HPP

#include <string>
#include "Point.hpp"
#include "Player.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#pragma once

void draw_grid(SDL_Renderer*, Player*);
void draw_point(SDL_Renderer* , Point&, int, int, SDL_Color);
void render_text(SDL_Renderer*, int, int, const char*, TTF_Font*, SDL_Rect*, SDL_Color&);
void free_ptr();
void load_map(std::string);

#endif