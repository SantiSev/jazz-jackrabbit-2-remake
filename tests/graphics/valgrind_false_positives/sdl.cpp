#include <iostream>

#include <SDL2/SDL.h>

// COMPILE WITH `g++ sdl.cpp -lSDL2 -o sdl`

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

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
