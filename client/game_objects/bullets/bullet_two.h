#ifndef BULLET_TWO_H
#define BULLET_TWO_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../../common/sfx_enum.h"
#include "../../../game_engine/gui/basic/resource_pool.h"
#include "../../../game_engine/gui/widgets/animated_sprite.h"

class BulletTwo: public engine::AnimatedSprite {
public:
    BulletTwo(const std::shared_ptr<engine::ResourcePool>& resource_pool, uint8_t direction, int x,
              int y):
            engine::AnimatedSprite(resource_pool->get_texture(SFX_FILE),
                                   resource_pool->get_yaml(SFX_FILE),
                                   map_bullet_to_animation_name.at(BULLET_TWO), x, y) {
        if (direction == 0) {
            this->flip();
        }
    }
};

#endif
