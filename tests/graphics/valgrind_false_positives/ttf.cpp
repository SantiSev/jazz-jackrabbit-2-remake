#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// COMPILE WITH `g++ ttf.cpp -lSDL2 -o ttf`

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

    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
