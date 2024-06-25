#include "health_bar_icon.h"

#define HEARTS_MARGIN 5

HealthBarIcon::HealthBarIcon(std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y,
                             int health):
        max_health(resource_pool->get_config()->player_health),
        health_per_hearts(max_health / MAX_HEARTS),
        bright_hearts(health / health_per_hearts) {
    auto yaml = *resource_pool->get_yaml(ICONS_FILE);
    SDL_Rect s_rect = {yaml["heart"]["x"].as<int>(), yaml["heart"]["y"].as<int>(),
                       yaml["heart"]["w"].as<int>(), yaml["heart"]["h"].as<int>()};
    SDL_Rect s_rect_dark = {yaml["dark-heart"]["x"].as<int>(), yaml["dark-heart"]["y"].as<int>(),
                            yaml["dark-heart"]["w"].as<int>(), yaml["dark-heart"]["h"].as<int>()};

    src_bright_hearts = s_rect;
    src_dark_hearts = s_rect_dark;

    SDL_Rect d_rect = {x, y, s_rect.w, s_rect.h};
    for (int i = 0; i < MAX_HEARTS; i++) {
        hearts.emplace_back(resource_pool->get_texture(ICONS_FILE), s_rect, d_rect);
        d_rect.x += d_rect.w + HEARTS_MARGIN;
    }
}

void HealthBarIcon::draw(SDL_Renderer* renderer, int it) {
    for (int i = 0; i < MAX_HEARTS; i++) {
        hearts[i].draw(renderer, it);
    }
}

void HealthBarIcon::update_health(int new_health) {
    bright_hearts = new_health / health_per_hearts;
    for (int i = 0; i < MAX_HEARTS; i++) {
        if (i < bright_hearts) {
            hearts[i].change_source(src_bright_hearts);
            continue;
        }
        hearts[i].change_source(src_dark_hearts);
    }
}

SDL_Rect& HealthBarIcon::get_body() { return hearts[0].get_body(); }

HealthBarIcon::~HealthBarIcon() = default;
