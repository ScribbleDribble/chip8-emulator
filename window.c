#include <stdio.h>

#include "SDL.h"
#include "system.h"


void window_loop(const char* file_path) {

    Chip8 chip8 = init_system(file_path);

    if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;

        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {
                SDL_Event event;
                
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);              
                decode(&chip8);

                for (int j=0; j < HEIGHT; j++)
                    for (int i=0; i < WIDTH; i++)
                    {
                        if (chip8.display[j][i] == 1)
                            SDL_RenderDrawPoint(renderer, i, j);
                    }
                SDL_RenderSetScale(renderer, 10, 10);
                SDL_RenderPresent(renderer);

                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) {
                        done = SDL_TRUE;
                    }
                }
            }
        }
        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}