
#include "../../../game_engine/controllers/keyboard.h"

#include <iostream>

#include "../../../game_engine/gui/widgets/button.h"

class Atus: public CanvasObject {
public:
    Atus() = default;
    void on_key_press(SDL_Keycode key) override {
        std::cout << "Key pressed: " << key << std::endl;
    }

    void draw(SDL_Renderer* renderer) override {}
    bool is_intersecting(SDL_Point& point) override { return false; }
    bool is_intersecting(SDL_Rect& rect) override { return false; }
};

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;
    SDL_Init(SDL_INIT_EVERYTHING);
    bool running = true;

    Keyboard keyboard;
    Atus atus;
    keyboard.add_on_key_down_signal_obj(&atus);

    SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer);
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

    return 0;
}
