#include "health_bar_icon.h"

#define HEARTS_MARGIN 5

HealthBarIcon::HealthBarIcon(std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y,
                             int health):
        health(health / 10) {
    auto yaml = *resource_pool->get_yaml(ICONS_FILE);
    SDL_Rect s_rect = {yaml["heart"]["x"].as<int>(), yaml["heart"]["y"].as<int>(),
                       yaml["heart"]["w"].as<int>(), yaml["heart"]["h"].as<int>()};
    SDL_Rect d_rect = {x, y, s_rect.w, s_rect.h};
    for (int i = 0; i < health; i++) {
        hearts.emplace_back(resource_pool->get_texture(ICONS_FILE), s_rect, d_rect);
        d_rect.x += d_rect.w + HEARTS_MARGIN;
    }
}

void HealthBarIcon::draw(SDL_Renderer* renderer, int it) {
    for (int i = 0; i < health; i++) {
        hearts[i].draw(renderer, it);
    }
}

void HealthBarIcon::update_health(int new_health) { health = new_health / 10; }

SDL_Rect& HealthBarIcon::get_body() { return hearts[0].get_body(); }

HealthBarIcon::~HealthBarIcon() = default;
