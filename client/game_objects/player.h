#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <iostream>
#include <utility>

#include <SDL2/SDL.h>

#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"

class Player: public engine::CanvasObject {
private:
    engine::AnimatedSprite sprite;

public:
    explicit Player(engine::AnimatedSprite&& sprite);

    void on_click() override;
    void on_key_press(const SDL_Keycode& key) override;

    void draw(SDL_Renderer* renderer) override;

    void set_position(int x, int y) override;

    bool is_intersecting(SDL_Point&) const override;
    bool is_intersecting(SDL_Rect&) const override;

    ~Player() override;
};


#endif  // TP_FINAL_PLAYER_H
