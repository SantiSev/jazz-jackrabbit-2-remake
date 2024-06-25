#include "character_selector.h"

CharacterSelector::CharacterSelector(std::shared_ptr<engine::ResourcePool> resource_pool,
                                     character_t character, int x, int y,
                                     character_t& selected_character,
                                     std::atomic<bool>& character_select_running):
        character(character),
        character_name(map_character_to_selector.at(character)),
        ripped_character_name(character_name + RIPPED_CHARACTER_APPEND),
        character_text_name(character_name + CHARACTER_TEXT_APPEND),
        character_text(nullptr),
        character_sprite(nullptr),
        ripped_character_sprite(nullptr),
        selected_character(selected_character),
        character_select_running(character_select_running),
        hovering(false) {
    auto texture = resource_pool->get_texture(CHARACTER_SELECT_FILE);
    auto yaml = *resource_pool->get_yaml(CHARACTER_SELECT_FILE);

    SDL_Rect text_s_rect = {
            yaml[character_text_name]["x"].as<int>(), yaml[character_text_name]["y"].as<int>(),
            yaml[character_text_name]["w"].as<int>(), yaml[character_text_name]["h"].as<int>()};

    SDL_Rect character_s_rect = {
            yaml[character_name]["x"].as<int>(), yaml[character_name]["y"].as<int>(),
            yaml[character_name]["w"].as<int>(), yaml[character_name]["h"].as<int>()};

    SDL_Rect ripped_character_s_rect = {
            yaml[ripped_character_name]["x"].as<int>(), yaml[ripped_character_name]["y"].as<int>(),
            yaml[ripped_character_name]["w"].as<int>(), yaml[ripped_character_name]["h"].as<int>()};

    character_text = std::make_unique<engine::Sprite>(
            texture, text_s_rect, SDL_Rect{x, y - 100, text_s_rect.w, text_s_rect.h});
    character_sprite = std::make_unique<engine::Sprite>(
            texture, character_s_rect, SDL_Rect{x, y, character_s_rect.w, character_s_rect.h});
    ripped_character_sprite = std::make_unique<engine::Sprite>(
            texture, ripped_character_s_rect,
            SDL_Rect{x, y, ripped_character_s_rect.w, ripped_character_s_rect.h});
}

void CharacterSelector::draw(SDL_Renderer* renderer, int it) {
    character_text->draw(renderer, it);
    if (hovering) {
        ripped_character_sprite->draw(renderer, it);
    } else {
        character_sprite->draw(renderer, it);
    }
}

void CharacterSelector::on_click() {
#ifdef LOG
    std::cout << "Character selected: " << (int)character << std::endl;
#endif
    selected_character = character;
    character_select_running.store(false);
}

void CharacterSelector::is_hovered(bool hovering_p) { hovering = hovering_p; }

SDL_Rect& CharacterSelector::get_body() { return character_sprite->get_body(); }

bool CharacterSelector::is_intersecting(SDL_Point& point) const {
    return character_sprite->is_intersecting(point);
}

CharacterSelector::~CharacterSelector() = default;
