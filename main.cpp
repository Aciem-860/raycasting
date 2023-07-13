#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Point.h"
#undef main
#pragma comment (lib, "SDL2.lib")
#pragma comment (lib, "SDL2main.lib")

#define PLAYER_W 10
#define PLAYER_H 10
#define GRID_W 40
#define GRID_H 40
#define WIDTH 680
#define HEIGHT 480
#define STEP_W 40
#define STEP_H 40
#define RED SDL_Color { 255, 0, 0, 0 }
#define GREEN SDL_Color { 0, 255, 0, 0 }
#define FONT_PATH "C:\\Users\\pierr\\Documents\\Visual Studio 2022\\Projects\\raycasting\\Minecraft.ttf"

using namespace std;

/* Variables globales*/

SDL_Event event;
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Surface* window_surface;
TTF_Font* font;
SDL_Rect* rect_pos = new SDL_Rect();

Point mouse_position = Point(0, 0);
Point target_position = Point(375, 230);
Point dir = target_position - mouse_position;

/* Déclaration des fonctions */

void update_dir();
void draw_grid();
void draw_point(Point&, int, int, SDL_Color);
void render_text(SDL_Renderer*, int, int, const char*, TTF_Font*, SDL_Rect*, SDL_Color&);
void get_intersection_points();
void free_ptr();

/* Définition des fonctions */

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Failed to initialize the SDL2 library : " << SDL_GetError() << endl;
        return -1;
    }

    if (TTF_Init() < 0) {
        cout << "Failed to initialize the TTF library : " << TTF_GetError() << endl;
        return -2;
    }
    window = SDL_CreateWindow("SDL2 Window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    font = TTF_OpenFont(FONT_PATH, 30);

    if (font == 0) {
        cout << "Erreur à l'ouverture de la police d'écriture" << endl;
        return -3;
    }

    if (!window) {
        cout << "Failed to create window" << endl;
        return -1;
    }

    SDL_Color foreground = { 255, 255, 0, 0 };
    window_surface = SDL_GetWindowSurface(window);

    if (!window_surface) {
        cout << "Failed to get the surface from the window" << endl;
        return -1;
    }

    bool fullscreen = false;
    bool quit = 0;
    
    while (!quit) {
        SDL_RenderClear(renderer);
        draw_grid();
        draw_point(mouse_position, PLAYER_W, PLAYER_H, RED);
        draw_point(target_position, PLAYER_W, PLAYER_H, GREEN);
        update_dir();

        string s = "X : " + to_string(mouse_position.getX()) + " ; Y : " + to_string(mouse_position.getY());
        const char* c = s.c_str();;
        SDL_Color yellow = SDL_Color { 255, 255, 0, 0 };
        render_text(renderer, 0, 0, c, font, rect_pos, yellow);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                quit = 1;
                break;
            case SDL_KEYUP:
                if (event.key.keysym.sym == SDLK_f) {
                    fullscreen = !fullscreen;
                    if (fullscreen) {
                        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
                    }
                    else {
                        SDL_SetWindowFullscreen(window, 0);
                    }
                }
                if (event.key.keysym.sym == SDLK_k) {
                    quit = 1;
                }
                if (event.key.keysym.sym == SDLK_z) {
                    target_position.setY(target_position.getY() - STEP_H);
                }
                if (event.key.keysym.sym == SDLK_q) {
                    target_position.setX(target_position.getX() - STEP_W);
                }
                if (event.key.keysym.sym == SDLK_s) {
                    target_position.setY(target_position.getY() + STEP_H);
                }
                if (event.key.keysym.sym == SDLK_d) {
                    target_position.setX(target_position.getX() + STEP_W);
                }
                break;
            case SDL_MOUSEMOTION:
                mouse_position.setX(event.motion.x);
                mouse_position.setY(event.motion.y);
            }
        }

        SDL_Delay(1);
    }
    free_ptr();
    SDL_FreeSurface(window_surface);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
}

void free_ptr() {
    delete rect_pos;
}

void update_dir() {
    dir = target_position - mouse_position;
}

void render_text(SDL_Renderer* renderer,
                int x,
                int y,
                const char* text,
                TTF_Font* font,
                SDL_Rect* rect,
                SDL_Color &color) {
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
void draw_grid() {
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
        SDL_RenderDrawLine(renderer, 0, j* GRID_H, WIDTH, j* GRID_H);
    }
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void draw_point(Point& point, int w, int h, SDL_Color color) {
    SDL_Rect rect;
    rect.x = point.getX() - w / 2;
    rect.y = point.getY() - h / 2;
    rect.w = w;
    rect.h = h;
    
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}