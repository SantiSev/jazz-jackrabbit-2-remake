#include "player.h"

Player::Player(engine::AnimatedSprite&& sprite, ClientMessageHandler& message_handler):
        sprite(std::move(sprite)), message_handler(message_handler) {}

void Player::on_click() {
    std::cout << "Player shot" << std::endl;
    message_handler.send_command(SHOOT);
}

void Player::on_key_press(const SDL_Keycode& key) {
    switch (key) {
        case SDLK_a:
            std::cout << "Player moved left" << std::endl;
            message_handler.send_command(MOVE_LEFT);
            break;
        case SDLK_d:
            std::cout << "Player moved right" << std::endl;
            message_handler.send_command(MOVE_RIGHT);
            break;
        case SDLK_SPACE:
            std::cout << "Player jumped" << std::endl;
            message_handler.send_command(JUMP);
            break;
        case SDLK_LSHIFT:
            std::cout << "Player toggled ran" << std::endl;
            // message_handler.send_command();
            break;
        case SDLK_e:
            std::cout << "Player activated special attack" << std::endl;
            message_handler.send_command(ESPECIAL_ATTACK);
            break;
        case SDLK_r:
            std::cout << "Player changed weapon" << std::endl;
            message_handler.send_command(CHANGE_WEAPON);
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
