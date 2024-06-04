#include "player.h"

Player::Player(engine::AnimatedSprite&& sprite): sprite(std::move(sprite)) { sprite.flip(); }

void Player::on_click() { std::cout << "Player shot" << std::endl; }

void Player::on_key_press(const SDL_Keycode& key) {
    switch (key) {
        case SDLK_a:
            std::cout << "Player moved left" << std::endl;
            break;
        case SDLK_d:
            std::cout << "Player moved right" << std::endl;
            break;
        case SDLK_SPACE:
            std::cout << "Player jumped" << std::endl;
            break;
        case SDLK_LSHIFT:
            std::cout << "Player toggled ran" << std::endl;
            break;
        case SDLK_e:
            std::cout << "Player activated special attack" << std::endl;
            break;
        case SDLK_r:
            std::cout << "Player changed weapon" << std::endl;
            break;
        default:
            std::cout << "Player pressed unknown key" << key << std::endl;
            break;
    }
}

void Player::update(int delta_time) { sprite.update(delta_time); }

void Player::draw(SDL_Renderer* renderer) { sprite.draw(renderer); }

void Player::set_position(int x, int y) { sprite.set_position(x, y); }

bool Player::is_intersecting(SDL_Point& point) const { return sprite.is_intersecting(point); }

bool Player::is_intersecting(SDL_Rect& rect) const { return sprite.is_intersecting(rect); }

Player::~Player() = default;
