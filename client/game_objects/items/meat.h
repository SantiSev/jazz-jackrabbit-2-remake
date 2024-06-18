#ifndef ITEM_MEAT_H
#define ITEM_MEAT_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../../common/item_enum.h"
#include "../../../game_engine/gui/basic/resource_pool.h"
#include "../../../game_engine/gui/widgets/animated_sprite.h"

class Meat: public engine::AnimatedSprite {
public:
    Meat(const std::shared_ptr<engine::ResourcePool>& resource_pool, int x, int y):
            engine::AnimatedSprite(resource_pool->get_texture(ITEMS_FILE),
                                   resource_pool->get_yaml(ITEMS_FILE),
                                   map_item_to_animation_name.at(MEAT), x, y) {}
};

#endif
