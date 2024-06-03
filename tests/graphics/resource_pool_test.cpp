#include "../../game_engine/gui/basic/resource_pool.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "../../game_engine/controllers/mouse.h"
#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/basic/window.h"
#include "../../game_engine/gui/widgets/sprite.h"

int main() {
    Window window(800, 600, true, false);
    auto renderer = window.getRenderer();

    ResourcePool resource_pool(renderer);
    resource_pool.load_texture("assets/screens.png");

    SDL_Event event;
    bool running = true;

    SDL_Rect rect = {16, 16, 640, 480};
    SDL_Rect d_rect = {0, 0, 800, 600};
    Sprite sprite(resource_pool.get_texture("assets/screens.png"), rect, d_rect);

    SDL_Rect rect2 = {660, 985, 640, 480};
    SDL_Rect d_rect2 = {0, 0, 400, 300};
    Sprite sprite2(resource_pool.get_texture("assets/screens.png"), rect2, d_rect2);

    Uint32 frame_start;
    int frame_time;
    const int frame_delay = 1000 / 60;

    while (running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        sprite.update(delta_time);
        sprite2.update(delta_time);

        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        window.clear();

        // Draw
        sprite.draw(renderer);
        sprite2.draw(renderer);

        window.render();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frame_delay - frame_time);
        }
    }

    return 0;
}
