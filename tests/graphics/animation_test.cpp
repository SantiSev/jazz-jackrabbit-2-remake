#include <iostream>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../../game_engine/gui/basic/asset_manager.h"
#include "../../game_engine/gui/basic/texture.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"

void run(SDL_Renderer*& renderer, SDL_Window*& window) {
    SDL_Event event;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Error initializing SDL:" << SDL_GetError() << std::endl;
        return;
    }

    bool running = true;

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

    engine::AssetManager asset_manager;

    auto texture = std::make_shared<engine::Texture>(asset_manager.get_full_path("assets/jazz.png"),
                                                     renderer);
    SDL_Rect rect = {0, 420, 53, 50};
    SDL_Rect d_rect = {0, 0, 800, 600};
    engine::AnimatedSprite sprite(texture, rect, d_rect, 13, 8);

    Uint32 frame_start = 0;
    int frame_time = 0;
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
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw
        sprite.draw(renderer, it);
        SDL_RenderPresent(renderer);

        frame_time = SDL_GetTicks() - frame_start;
        if (frame_delay > frame_time) {  // Delay to achieve 60 fps
            SDL_Delay(frame_delay - frame_time);
        }
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
