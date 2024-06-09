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

class Player: public engine::CanvasObject {
private:
    engine::AnimatedSprite sprite;
    ClientMessageHandler& message_handler;

public:
    Player(engine::AnimatedSprite&& sprite, ClientMessageHandler& message_handler);

    void on_click() override;
    void on_key_press(const SDL_Keycode& key) override;

    void update(int delta_time) override;
    void draw(SDL_Renderer* renderer) override;

    void set_position(int x, int y) override;
    void set_animation(const std::string& animation_name);

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~Player() override;
};


#endif  // TP_FINAL_PLAYER_H
