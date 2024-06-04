#include "player.h"

Player::Player(engine::AnimatedSprite&& sprite, Queue<std::shared_ptr<Message>>& sender_queue):
        sprite(std::move(sprite)), sender_queue(sender_queue) {}

void Player::on_click() {
    std::cout << "Player shot" << std::endl;
    CommandDTO dto = {0, SHOT};
    sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
}

void Player::on_key_press(const SDL_Keycode& key) {
    CommandDTO dto;
    dto.id_player = 0;

    switch (key) {
        case SDLK_a:
            std::cout << "Player moved left" << std::endl;
            dto.command = MOVE_LEFT;
            sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
            break;
        case SDLK_d:
            std::cout << "Player moved right" << std::endl;
            dto.command = MOVE_RIGHT;
            sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
            break;
        case SDLK_SPACE:
            std::cout << "Player jumped" << std::endl;
            dto.command = JUMP;
            sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
            break;
        case SDLK_LSHIFT:
            std::cout << "Player toggled ran" << std::endl;
            // dto.command;
            // sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
            break;
        case SDLK_e:
            std::cout << "Player activated special attack" << std::endl;
            dto.command = ESPECIAL_ATTACK;
            sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
            break;
        case SDLK_r:
            std::cout << "Player changed weapon" << std::endl;
            dto.command = CHANGE_WEAPON;
            sender_queue.push(std::make_shared<RecvCommandMessage>(dto));
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
