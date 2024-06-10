#ifndef TP_FINAL_JAZZ_H
#define TP_FINAL_JAZZ_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../../common/character_enum.h"
#include "../../../game_engine/gui/basic/resource_pool.h"
#include "../../../game_engine/gui/widgets/animated_sprite.h"

class Jazz: public engine::AnimatedSprite {
public:
    Jazz(const std::shared_ptr<engine::ResourcePool>& resource_pool,
         const std::string& animation_name, int x, int y):
            engine::AnimatedSprite(
                    resource_pool->get_texture(map_character_enum_to_string.at(JAZZ_CHARACTER)),
                    resource_pool->get_yaml(map_character_enum_to_string.at(JAZZ_CHARACTER)),
                    animation_name, x, y) {}
};


#endif  // TP_FINAL_JAZZ_H
