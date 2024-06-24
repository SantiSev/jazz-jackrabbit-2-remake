#include "bullet_icon.h"

BulletIcon::BulletIcon(SDL_Renderer* renderer, std::shared_ptr<engine::ResourcePool> resource_pool,
                       int x, int y, int amount, bullet_type_t bullet_type):
        icon(nullptr), amount_label(nullptr) {
    auto yaml = *resource_pool->get_yaml(ICONS_FILE);
    std::string sprite_name = map_bullet_to_animation_name.at(bullet_type);
    int s_x = yaml[sprite_name]["x"].as<int>();
    int s_y = yaml[sprite_name]["y"].as<int>();
    int s_w = yaml[sprite_name]["w"].as<int>();
    int s_h = yaml[sprite_name]["h"].as<int>();

    SDL_Rect s_rect = {s_x, s_y, s_w, s_h};
    SDL_Rect d_rect = {x, y, int(s_w * 1.5), int(s_h * 1.5)};

    icon = std::make_unique<engine::Sprite>(resource_pool->get_texture(ICONS_FILE), s_rect, d_rect);
    amount_label = std::make_unique<engine::Label>(
            resource_pool->get_font(FONT), SDL_Rect{d_rect.x + d_rect.w + 5, d_rect.y, 0, 0},
            SDL_Color{0, 0, 0, 255}, SDL_Color{0, 0, 0, 255}, "Score: " + std::to_string(amount),
            renderer);
}

void BulletIcon::draw(SDL_Renderer* renderer, int it) {
    icon->draw(renderer, it);
    amount_label->draw(renderer, it);
}

void BulletIcon::update_amount(int new_amount, SDL_Renderer* renderer) {
    amount_label->set_text(std::to_string(new_amount), renderer);
}

SDL_Rect& BulletIcon::get_body() { return icon->get_body(); }

BulletIcon::~BulletIcon() = default;
