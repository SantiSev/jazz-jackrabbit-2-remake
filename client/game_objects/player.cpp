#include "player.h"

Player::Player(engine::AnimatedSprite&& sprite, ClientMessageHandler& message_handler):
        sprite(std::move(sprite)), message_handler(message_handler) {}

void Player::on_click() {
#ifdef LOG_VERBOSE
    std::cout << "Player clicked" << std::endl;
#endif
    message_handler.send_command(SHOOT);
}

void Player::on_key_press(const SDL_Keycode& key) {
    switch (key) {
        case SDLK_a:
            message_handler.send_command(MOVE_LEFT);
            break;
        case SDLK_d:
            message_handler.send_command(MOVE_RIGHT);
            break;
        case SDLK_SPACE:
            message_handler.send_command(JUMP);
            break;
        case SDLK_LSHIFT:
            // message_handler.send_command();
            break;
        case SDLK_e:
            message_handler.send_command(SPECIAL_ATTACK);
            break;
        case SDLK_r:
            message_handler.send_command(CHANGE_WEAPON);
            break;
        default:
            break;
    }
#ifdef LOG_VERBOSE
    std::cout << "Player pressed key: " << key << std::endl;
#endif
}

void Player::update(int delta_time) { sprite.update(delta_time); }

void Player::draw(SDL_Renderer* renderer) { sprite.draw(renderer); }

void Player::set_position(int x, int y) { sprite.set_position(x, y); }

void Player::set_animation(const std::string& animation_name) {
    sprite.set_animation(animation_name);
}

bool Player::is_intersecting(SDL_Point& point) const { return sprite.is_intersecting(point); }

bool Player::is_intersecting(SDL_Rect& rect) const { return sprite.is_intersecting(rect); }

Player::~Player() = default;
