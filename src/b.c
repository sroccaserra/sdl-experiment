#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "b.h"
#include "m.h"

#define LOGICAL_WIDTH 512
#define LOGICAL_HEIGHT 342
#define ZOOM 2

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

#define NB_POINTS 512
#define MAX_X 255
#define MAX_Y 255

#define MARGIN 20

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
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Error initializing SDL.\n");
        return false;
    }

    window = SDL_CreateWindow(
        "A simple game loop using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LOGICAL_WIDTH*ZOOM,
        LOGICAL_HEIGHT*ZOOM,
        0
    );

    if (!window) {
        fprintf(stderr, "Error creating SDL Window.\n");
        return false;
    }

    const int rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer = SDL_CreateRenderer(window, -1, rendererFlags);
    if (!renderer) {
        fprintf(stderr, "Error creating SDL Renderer.\n");
        return false;
    }

    SDL_RenderSetLogicalSize(renderer, LOGICAL_WIDTH, LOGICAL_HEIGHT);

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
    for (size_t i = 0; i < NB_POINTS; ++i) {
        struct Point* point = &points[i];
        point->x = rand()%MAX_X;
        point->y = rand()%MAX_Y;
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

    struct Point transformed[NB_POINTS];
    float min_x = MARGIN;
    float max_x = LOGICAL_WIDTH-MARGIN;
    float min_y = MARGIN;
    float max_y = LOGICAL_HEIGHT-MARGIN;
    for (size_t i = 0; i< NB_POINTS; ++i) {
        struct Point* p = &points[i];
        struct Point* t = &transformed[i];
        t->x = remap(0, MAX_X, min_x, max_x, p->x);
        t->y = remap(0, MAX_Y, min_y, max_y, p->y);
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPointsF(renderer, (SDL_FPoint*)transformed, NB_POINTS);

    SDL_RenderPresent(renderer);
}

void destroy_window() {
    if (NULL != renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (NULL != window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
}
