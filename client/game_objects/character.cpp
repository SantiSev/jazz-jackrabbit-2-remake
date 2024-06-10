#include "character.h"

Character::Character(std::unique_ptr<engine::AnimatedSprite> sprite): sprite(std::move(sprite)) {}

void Character::update(int delta_time) { sprite->update(delta_time); }

void Character::draw(SDL_Renderer* renderer) { sprite->draw(renderer); }

void Character::set_position(int x, int y) { sprite->set_position(x, y); }

void Character::set_animation(const std::string& animation_name) {
    sprite->set_animation(animation_name);
}

Character::~Character() = default;
