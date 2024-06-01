#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// COMPILE WITH `g++ img.cpp -lSDL2 -o sdl`

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
