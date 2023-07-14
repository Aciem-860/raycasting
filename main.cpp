#include "main.hpp"

using namespace std;

Player* player = new Player(100, 100, FOV);

int main() {
    SDL_Event event;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* window_surface;
    TTF_Font* font;


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
        draw_grid(renderer, player);
        draw_point(renderer, *(player->get_pos()), PLAYER_W, PLAYER_H, RED);
        //draw_point(renderer, target_position, PLAYER_W, PLAYER_H, GREEN);

        string s = "X : " + to_string(player->get_pos()->getX()) + " ; Y : " + to_string(player->get_pos()->getY());
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
                    //target_position.setY(target_position.getY() - STEP_H);
                }
                if (event.key.keysym.sym == SDLK_q) {
                    player->rotate(-20);
                    //target_position.setX(target_position.getX() - STEP_W);
                }
                if (event.key.keysym.sym == SDLK_s) {
                    //target_position.setY(target_position.getY() + STEP_H);
                }
                if (event.key.keysym.sym == SDLK_d) {
                    player->rotate(+20);
                    //target_position.setX(target_position.getX() + STEP_W);
                }
                break;
            case SDL_MOUSEMOTION:
                Point mouse_pos = Point(event.motion.x, event.motion.y);
                player->move(mouse_pos);
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
    delete player;
}