#include "editor_controller.h"

#define EDITOR_MOVEMENT_SPEED 32

EditorController::EditorController(engine::Camera& camera, EventLoop* event_loop):
        camera(camera), event_loop(event_loop) {
    event_loop->keyboard.add_on_key_down_signal_obj(this);
}

void EditorController::on_key_press(const SDL_Keycode& key) {
    switch (key) {
        case SDLK_a:
            camera.move_pos(camera.get_body().x - EDITOR_MOVEMENT_SPEED, -1);
            break;
        case SDLK_d:
            camera.move_pos(camera.get_body().x + EDITOR_MOVEMENT_SPEED, -1);
            break;
        case SDLK_w:
            camera.move_pos(-1, camera.get_body().y - EDITOR_MOVEMENT_SPEED);
            break;
        case SDLK_s:
            camera.move_pos(-1, camera.get_body().y + EDITOR_MOVEMENT_SPEED);
            break;
        default:
            break;
    }
#ifdef LOG
    std::cout << "EditorController key pressed " << (char)key << std::endl;
#endif
}

void EditorController::draw(SDL_Renderer* renderer, int it) {}

SDL_Rect& EditorController::get_body() { return camera.get_body(); }

EditorController::~EditorController() { event_loop->keyboard.remove_on_key_down_signal_obj(this); }
