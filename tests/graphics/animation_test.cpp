#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../game_engine/gui/widgets/animated_sprite.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);

    bool running = true;

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);

    IMG_Init(IMG_INIT_PNG);
    AnimatedSprite sprite("/home/maxo/Desktop/taller/assets/jazz.png", {0, 1682, 218, 198},
                          {0, 0, 800, 600}, 13, 1);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        sprite.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(1);
    }
    return 0;
}
