#include "../../game_engine/gui/widgets/button.h"

#include <exception>
#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "../../game_engine/controllers/mouse.h"
#include "../../game_engine/gui/basic/font.h"
#include "../../game_engine/gui/widgets/label.h"

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
        return 1;
    }

    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0) {
        std::cerr << "Error creating window and renderer:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    if (TTF_Init() < 0) {
        std::cerr << "Error initializing TTF:" << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    bool running = true;

    {
        auto font =
                std::make_shared<Font>("/home/maxo/Desktop/taller/game_engine/fonts/atus.ttf", 15);

        Mouse mouse(0, 0);

        SDL_Rect rect_label = {300, 200, 100, 100};
        Label label(font, rect_label, {0, 0, 0}, {255, 255, 255}, "Hello", renderer);

        SDL_Rect rect = {300, 200, 100, 100};
        Button button(std::move(label), rect, {255, 255, 255}, {0, 0, 0});
        mouse.add_on_click_signal_obj(&button);

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
    }

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
