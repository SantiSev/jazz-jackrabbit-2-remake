#include "player_controller.h"

PlayerController::PlayerController(ClientMessageHandler& message_handler):
        message_handler(message_handler), body({0, 0, 0, 0}) {}

void PlayerController::on_click() { message_handler.send_command(SHOOT); }

void PlayerController::on_key_press(const SDL_Keycode& key) {
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
            message_handler.send_command(SPRINT);
            break;
        case SDLK_e:
            message_handler.send_command(SPECIAL_ATTACK);
            break;
        case SDLK_r:
            message_handler.send_command(CHANGE_WEAPON);
            break;
        case SDLK_1:
            message_handler.send_cheat_command(CHEAT_MAX_AMMO);
            break;
        case SDLK_2:
            message_handler.send_cheat_command(CHEAT_MAX_HEALTH);
            break;
        case SDLK_3:
            message_handler.send_cheat_command(CHEAT_INVINCIBLE);
            break;
        case SDLK_4:
            message_handler.send_cheat_command(CHEAT_REVIVE);
            break;
        case SDLK_5:
            message_handler.send_cheat_command(CHEAT_INFINITE_AMMO);
            break;
        case SDLK_6:
            message_handler.send_cheat_command(CHEAT_KILL_ALL);
            break;
        default:
            break;
    }
}

void PlayerController::on_key_release(const SDL_Keycode& key) {
    switch (key) {
        case SDLK_a:
            message_handler.send_command(STOP_MOVE_LEFT);
            break;
        case SDLK_d:
            message_handler.send_command(STOP_MOVE_RIGHT);
            break;
        case SDLK_LSHIFT:
            message_handler.send_command(STOP_SPRINT);
            break;
        default:
            break;
    }
}

void PlayerController::draw(SDL_Renderer* renderer, int it) {}

SDL_Rect& PlayerController::get_body() { return body; }

// It should be clickable anywhere
bool PlayerController::is_intersecting(SDL_Point& point) const { return true; }

PlayerController::~PlayerController() = default;
