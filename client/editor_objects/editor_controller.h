#ifndef TP_FINAL_EDITOR_CONTROLLER_H
#define TP_FINAL_EDITOR_CONTROLLER_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common/common_queue.h"
#include "../../game_engine/gui/camera.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "../event_loop.h"

class EditorController: public engine::CanvasObject {
private:
    engine::Camera& camera;
    EventLoop* event_loop;

public:
    explicit EditorController(engine::Camera& camera, EventLoop* event_loop);

    void on_key_press(const SDL_Keycode& key) override;

    void draw(SDL_Renderer* renderer, int it) override;
    SDL_Rect& get_body() override;

    ~EditorController();
};


#endif  // TP_FINAL_EDITOR_CONTROLLER_H
