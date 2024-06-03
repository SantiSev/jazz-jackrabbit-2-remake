#include "../../game_engine/gui/widgets/color_rect.h"

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

void run(SDL_Renderer*& renderer, SDL_Window*& window) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
        return;
    }

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0) {
        std::cerr << "Error creating window and renderer:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "Error initializing SDL_image:" << IMG_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_Event event;
    bool running = true;

    SDL_Rect rect = {16, 16, 640, 480};
    SDL_Color color = {255, 255, 255, 255};
    ColorRect color_rect(color, rect);

    Uint32 frame_start;
    int frame_time;
    const int frame_delay = 1000 / 60;

    while (running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        color_rect.update(delta_time);

        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw
        color_rect.draw(renderer);
        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frame_delay - frame_time);
        }
    }
}

void clean(SDL_Renderer* renderer, SDL_Window* window) {
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    run(renderer, window);
    clean(renderer, window);

    return 0;
}
