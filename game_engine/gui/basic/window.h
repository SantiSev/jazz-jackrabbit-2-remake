#ifndef TP_FINAL_WINDOW_H
#define TP_FINAL_WINDOW_H

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../errors.h"

namespace engine {
class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;

public:
    Window(int width, int height, bool img_init, bool ttf_init);

    // Cant copy or move
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    void clear();
    void render();

    SDL_Window* get_window() const;
    SDL_Renderer* get_renderer() const;

    int get_width() const;
    int get_height() const;

    ~Window();
};
}  // namespace engine

#endif  // TP_FINAL_WINDOW_H
