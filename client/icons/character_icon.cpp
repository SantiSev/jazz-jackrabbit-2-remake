#include "character_icon.h"

CharacterIcon::CharacterIcon(std::shared_ptr<engine::ResourcePool> resource_pool, int x, int y,
                             character_t character_type) {
    auto yaml = *resource_pool->get_yaml(ICONS_FILE);
    SDL_Rect s_rect = {yaml[map_character_enum_to_icon_name.at(character_type)]["x"].as<int>(),
                       yaml[map_character_enum_to_icon_name.at(character_type)]["y"].as<int>(),
                       yaml[map_character_enum_to_icon_name.at(character_type)]["w"].as<int>(),
                       yaml[map_character_enum_to_icon_name.at(character_type)]["h"].as<int>()};
    SDL_Rect d_rect = {x, y, int(s_rect.w * 1.5), int(s_rect.h * 1.5)};
    icon = std::make_unique<engine::Sprite>(resource_pool->get_texture(ICONS_FILE), s_rect, d_rect);
}

void CharacterIcon::draw(SDL_Renderer* renderer, int it) { icon->draw(renderer, it); }

SDL_Rect& CharacterIcon::get_body() { return icon->get_body(); }

CharacterIcon::~CharacterIcon() = default;
