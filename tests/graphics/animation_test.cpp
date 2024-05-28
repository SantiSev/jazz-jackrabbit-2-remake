#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../game_engine/gui/widgets/animated_sprite.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
        return 1;
    }

    bool running = true;

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0) {
        std::cerr << "Error creating window and renderer:" << SDL_GetError() << std::endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Error initializing SDL_image:" << IMG_GetError() << std::endl;
        return 1;
    }

    AnimatedSprite sprite("/home/maxo/Desktop/taller/assets/jazz.png", {0, 420, 53, 50},
                          {0, 0, 800, 600}, 13, 8, renderer);

    Uint32 frame_start;
    int frame_time;
    const int frameDelay = 1000 / 60;

    while (running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        sprite.update(delta_time);

        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw
        sprite.draw(renderer);
        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - frame_start;
        if (frameDelay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frameDelay - frame_time);
        }
    }

    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
