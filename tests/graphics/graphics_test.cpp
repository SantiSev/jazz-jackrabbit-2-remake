#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../game_engine/controllers/mouse.h"
#include "../../game_engine/gui/widgets/button.h"
#include "../../game_engine/gui/widgets/label.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font* font = TTF_OpenFont("/home/maxo/Desktop/taller/game_engine/fonts/atus.ttf", 15);

    bool running = true;

    Mouse mouse(0, 0);
    Label label({300, 200, 100, 100}, {0, 0, 0}, {255, 255, 255}, "Hello, World!", font);
    Button button({300, 200, 100, 100}, {255, 255, 255}, {0, 0, 0}, label);

    mouse.add_on_click_signal_obj(&button);

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            mouse.update(event);
        }
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        button.draw(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    return 0;
}
