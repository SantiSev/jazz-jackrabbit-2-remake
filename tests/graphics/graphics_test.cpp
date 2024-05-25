#include <exception>
#include <iostream>

#include <SDL2/SDL.h>

#include "../../game_engine/controllers/mouse.h"
#include "../../game_engine/gui/widgets/button.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    Mouse mouse(0, 0);
    Button button({0, 0, 100, 100}, {255, 255, 255, 255}, {0, 0, 0, 0});

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            mouse.update(event);
            button.update(mouse);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        button.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return 0;
}
