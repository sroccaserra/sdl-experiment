#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "ab.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)
#define NB_POINTS 256

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

bool game_is_running = false;
int last_frame_time = 0;

struct Point {
    float x;
    float y;
};

struct Point points[NB_POINTS];

int initialize_window() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0
    );

    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    return true;
}

void process_input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game_is_running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game_is_running = false;
                }
                break;
        }
    }
}

void setup() {
    size_t i;
    for (i = 0; i < NB_POINTS; ++i) {
        struct Point* point = &points[i];
        point->x = i;
        point->y = i/2;
    }
}

void update() {
    /*float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0;*/
    last_frame_time = SDL_GetTicks();
}

void cls() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void render() {
    cls();

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPointsF(renderer, (SDL_FPoint*)points, NB_POINTS);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
