#include "../../game_engine/gui/widgets/sprite.h"

#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "../../game_engine/controllers/mouse.h"
#include "../../game_engine/gui/basic/asset_manager.h"
#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/basic/window.h"

int main() {
    engine::Window window(800, 600, true, false);

    auto renderer = window.getRenderer();

    engine::AssetManager asset_manager;

    SDL_Event event;
    bool running = true;
    auto texture = std::make_shared<engine::Texture>(
            asset_manager.get_full_path("assets/screens.png"), renderer);
    SDL_Rect rect = {16, 16, 640, 480};
    SDL_Rect d_rect = {0, 0, 800, 600};
    engine::Sprite sprite(texture, rect, d_rect);

    Uint32 frame_start;
    int frame_time;
    const int frame_delay = 1000 / 60;

    while (running) {
        // Updates
        int delta_time = SDL_GetTicks() - frame_start;
        sprite.update(delta_time);

        frame_start = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        window.clear();

        // Draw
        sprite.draw(renderer);

        window.render();

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frame_delay - frame_time);
        }
    }

    return 0;
}