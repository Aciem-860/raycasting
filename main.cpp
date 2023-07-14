#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cmath>
#include <vector>
#include <iterator>
#include <fstream>
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
#define STEP_W 10
#define STEP_H 10
#define RED SDL_Color { 255, 0, 0, 0 }
#define GREEN SDL_Color { 0, 255, 0, 0 }
#define YELLOW SDL_Color { 255, 255, 0, 0 }
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

char map_array[HEIGHT / GRID_H][WIDTH / GRID_W] = {{ 0 }};

/* Déclaration des fonctions */

void update_dir();
void draw_grid();
void draw_point(Point&, int, int, SDL_Color);
void render_text(SDL_Renderer*, int, int, const char*, TTF_Font*, SDL_Rect*, SDL_Color&);
void free_ptr();
void load_map(string);
void compute_intersection_points();
Point get_intersection_points(Point&, Point&);

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

    load_map("map.txt");
    for (int x = 0; x < HEIGHT / GRID_H; x++) {
        for (int y = 0; y < WIDTH / GRID_W; y++) {
            cout << int(map_array[x][y]);
        }
        cout << endl;
    }

    while (!quit) {
        SDL_RenderClear(renderer);
        draw_grid();
        draw_point(mouse_position, PLAYER_W, PLAYER_H, RED);
        draw_point(target_position, PLAYER_W, PLAYER_H, GREEN);
        update_dir();
        compute_intersection_points();

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
        SDL_RenderDrawLine(renderer, 0, j * GRID_H, WIDTH, j* GRID_H);
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

void compute_intersection_points() {
    vector<Point> pts = vector<Point>();
    pts.push_back(mouse_position);
    Point p = Point(0, 0);
    bool quit = false;
    bool intersect = false;

    while (!quit) {
        //draw_point(pts.back(), 5, 5, SDL_Color{255, 255, 0, 0});
        p = get_intersection_points(pts.back(), dir);
        // On vérifie que le point regardé est bien entre le carré vert et le carré rouge
        quit = !((p.getX() < mouse_position.getX() && p.getX() > target_position.getX()) || ((p.getX() > mouse_position.getX() && p.getX() < target_position.getX())));
        int x = p.getX();
        int y = p.getY();

        x /= GRID_W;
        y /= GRID_H;
        
        if (int(p.getX()) % GRID_W == 0)
            x = x - (dir.getX() < 0 ? 1 : 0);
        if (int(p.getY()) % GRID_H == 0)
            y = y - (dir.getY() < 0 ? 1 : 0);

        intersect = (map_array[y][x] != 0) ? true : false;

        if (intersect) {
            quit = true;
            pts.push_back(p);
            draw_point(p, 5, 5, YELLOW);
        }
        if (!quit)
            pts.push_back(p);
    }

    /*if (intersect)
        draw_point(pts.back(), 5, 5, SDL_Color{ 255, 255, 0, 0 });*/
}


// Donne les points d'intersection avec la grille (pas avec les blocs !!)
Point get_intersection_points(Point &point, Point &dir) {
    double dx, dy;
    
    dx = int(point.getX()) % GRID_W; // le pas unitaire en x
    if (dx == 0)
        dx = GRID_W;

    dy = int(point.getY()) % GRID_H; // le pas unitaire en y
    if (dy == 0)
        dy = GRID_H;

    if (dir.getX() > 0 && dx != GRID_W)
        dx = GRID_W - dx;

    if (dir.getY() > 0 && dy != GRID_H)
        dy = GRID_H - dy;

    double lx = dx * sqrt(1 + 1 / pow(dir.getSlope(), 2));
    double ly = dy * sqrt(1 + pow(dir.getSlope(), 2));

    dx = dx * ((dir.getX() < 0) ? -1 : 1);
    dy = dy * ((dir.getY() < 0) ? -1 : 1);

    Point intersect = Point(0, 0);

    if (lx < ly) {
        intersect.setX(point.getX() + dx);
        intersect.setY(point.getY() + dx / dir.getSlope());
    }
    else {
        intersect.setX(point.getX() + dy * dir.getSlope());
        intersect.setY(point.getY() + dy);
    }

    return intersect;
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