#ifndef FUNC_GFX_CPP
#define FUNC_GFX_CPP

#include <vector>
#include <cstring>
#include <string>
#include <cstdio>
#include <fstream>
#include <iostream>
#include "funcs_gfx.hpp"
#include "global_vars.hpp"
#include "Point.hpp"

using namespace std;

void update_dir() {
    dir = target_position - mouse_position;
}

void render_text(SDL_Renderer* renderer,
    int x,
    int y,
    const char* text,
    TTF_Font* font,
    SDL_Rect* rect,
    SDL_Color& color) {
    SDL_Surface* surface;
    SDL_Texture* texture;

    surface = TTF_RenderText_Solid(font, text, color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}
void draw_grid(SDL_Renderer* renderer) {
    // Tracé de la grille

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer,
        mouse_position.getX(),
        mouse_position.getY(),
        target_position.getX(),
        target_position.getY());

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    for (int i = 0; i < WIDTH / GRID_W; i++) {
        SDL_RenderDrawLine(renderer, i * GRID_W, 0, i * GRID_W, HEIGHT);
    }
    for (int j = 0; j < HEIGHT / GRID_H; j++) {
        SDL_RenderDrawLine(renderer, 0, j * GRID_H, WIDTH, j * GRID_H);
    }

    // Tracé des blocs

    SDL_Rect* block = new SDL_Rect();
    block->w = GRID_W;
    block->h = GRID_H;

    for (int i = 0; i < HEIGHT / GRID_H; i++) {
        for (int j = 0; j < WIDTH / GRID_W; j++) {
            if (map_array[i][j] != 0) {
                SDL_SetRenderDrawColor(renderer, 140, 124, 73, 0);
                block->x = j * GRID_W;
                block->y = i * GRID_H;
                SDL_RenderFillRect(renderer, block);
            }
        }
    }

    delete block;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void draw_point(SDL_Renderer* renderer, Point& point, int w, int h, SDL_Color color) {
    SDL_Rect rect;
    rect.x = point.getX() - w / 2;
    rect.y = point.getY() - h / 2;
    rect.w = w;
    rect.h = h;

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void load_map(string path) {
    string line;
    ifstream map(path);
    int i = 0;
    int j = 0;
    if (map.is_open()) {
        while (getline(map, line)) {
            for (string::iterator it = line.begin(); it < line.end(); it++) {
                map_array[i][j] = *it - 48;
                j++;
            }
            i++;
            j = 0;
        }

        map.close();
    }
    else {
        cout << "Unable to open the file : " << path << endl;
    }
}

#endif