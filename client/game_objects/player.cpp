#include "player.h"

PlayerController::PlayerController(ClientMessageHandler& message_handler):
        message_handler(message_handler) {}

void PlayerController::on_click() {
#ifdef LOG
    std::cout << "PlayerController clicked" << std::endl;
#endif
    message_handler.send_command(SHOOT);
}

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
    std::cout << "PlayerController pressed key: " << key << std::endl;
#endif
}

void PlayerController::draw(SDL_Renderer* renderer) {}

// It should be clickable anywhere
bool PlayerController::is_intersecting(SDL_Point& point) const { return true; }

PlayerController::~PlayerController() = default;
