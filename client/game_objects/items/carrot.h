#ifndef ITEM_CARROT_H
#define ITEM_CARROT_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../../common/item_enum.h"
#include "../../../game_engine/gui/basic/resource_pool.h"
#include "../../../game_engine/gui/widgets/animated_sprite.h"

class Carrot: public engine::AnimatedSprite {
public:
    Carrot(const std::shared_ptr<engine::ResourcePool>& resource_pool, int x, int y):
            engine::AnimatedSprite(resource_pool->get_texture(ITEMS_FILE),
                                   resource_pool->get_yaml(ITEMS_FILE),
                                   map_item_to_animation_name.at(CARROT), x, y) {}
};

#endif
