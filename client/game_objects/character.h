#ifndef TP_FINAL_CHARACTER_H
#define TP_FINAL_CHARACTER_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../common/common_queue.h"
#include "../../game_engine/gui/canvas_object.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"

class Character: public engine::CanvasObject {
private:
    std::unique_ptr<engine::AnimatedSprite> sprite;

public:
    explicit Character(std::unique_ptr<engine::AnimatedSprite> sprite);

    void update(int delta_time) override;
    void draw(SDL_Renderer* renderer) override;

    void set_position(int x, int y) override;
    void set_animation(const std::string& animation_name);

    virtual ~Character();
};

#endif  // TP_FINAL_CHARACTER_H
