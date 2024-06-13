#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common/common_queue.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "../protocol/client_message_handler.h"

class ClientMessageHandler;

class PlayerController: public engine::CanvasObject {
private:
    ClientMessageHandler& message_handler;

public:
    explicit PlayerController(ClientMessageHandler& message_handler);
    void on_click() override;
    void on_key_press(const SDL_Keycode& key) override;

    void draw(SDL_Renderer* renderer, int it) override;

    bool is_intersecting(SDL_Point& point) const override;

    ~PlayerController();
};


#endif  // TP_FINAL_PLAYER_H
