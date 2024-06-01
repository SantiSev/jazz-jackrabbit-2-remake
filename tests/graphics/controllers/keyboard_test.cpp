
#include "../../../game_engine/controllers/keyboard.h"

#include <iostream>

#include <SDL2/SDL.h>

#include "../../../game_engine/gui/widgets/button.h"

class KeyboardTestLabRat: public CanvasObject {
public:
    KeyboardTestLabRat() = default;
    void on_key_press(SDL_Keycode key) override {
        std::cout << "Key pressed: " << key << std::endl;
    }

    void draw(SDL_Renderer* renderer) override {}
    void set_position(int x, int y) override {}
    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};

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

    SDL_Event event;
    bool running = true;

    {
        Keyboard keyboard;
        KeyboardTestLabRat lab_rat;
        keyboard.add_on_key_down_signal_obj(&lab_rat);

        while (running) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;
                }
                keyboard.update(event);
            }
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_RenderClear(renderer);

            SDL_RenderPresent(renderer);
            SDL_Delay(10);
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
