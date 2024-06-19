#include "window.h"

using engine::Window;

Window::Window(int width, int height, bool img_init, bool ttf_init): width(width), height(height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        throw SDLError("Error initializing SDL:" + std::string(SDL_GetError()));
    }

    if (SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer) < 0) {
        throw SDLError("Error creating window and renderer:" + std::string(SDL_GetError()));
    }

    if (img_init && IMG_Init(IMG_INIT_PNG) == 0) {
        throw SDLError("Error initializing SDL_image:" + std::string(IMG_GetError()));
    }

    if (ttf_init && TTF_Init() < 0) {
        throw SDLError("Error initializing SDL_ttf:" + std::string(TTF_GetError()));
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        throw SDLError("Error initializing SDL_Mixer:" + std::string(Mix_GetError()));
    }
}

void Window::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Window::render() { SDL_RenderPresent(renderer); }

SDL_Window* Window::get_window() const { return window; }

SDL_Renderer* Window::get_renderer() const { return renderer; }

int Window::get_width() const { return width; }

int Window::get_height() const { return height; }

Window::~Window() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}
