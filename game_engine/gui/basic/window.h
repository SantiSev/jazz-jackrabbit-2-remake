#ifndef TP_FINAL_WINDOW_H
#define TP_FINAL_WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../../errors.h"

class Window {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;

public:
    Window(int width, int height, bool img_init, bool ttf_init);

    void clear();
    void render();

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

    ~Window();
};

#endif //TP_FINAL_WINDOW_H