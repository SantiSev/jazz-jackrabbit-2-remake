#include "background.h"

MainScreenBackground::MainScreenBackground(const engine::ResourcePool& resource_pool):
        sprite(nullptr) {
    auto yaml = *resource_pool.get_yaml(BACKGROUNDS_FILE);
    auto background = yaml[MAIN_MENU_3];

    background_s_rect.x = background["x"].as<int>();
    background_s_rect.y = background["y"].as<int>();
    background_s_rect.w = background["w"].as<int>();
    background_s_rect.h = background["h"].as<int>();
    background_d_rect = {0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT};

    sprite = std::make_unique<engine::Sprite>(resource_pool.get_texture(BACKGROUNDS_FILE),
                                              background_s_rect, background_d_rect);
}

void MainScreenBackground::draw(SDL_Renderer* renderer, int it) { sprite->draw(renderer, it); }

SDL_Rect& MainScreenBackground::get_body() { return background_d_rect; }
