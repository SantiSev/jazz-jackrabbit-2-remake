#ifndef TP_FINAL_SPAZ_H
#define TP_FINAL_SPAZ_H

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <SDL2/SDL.h>

#include "../../../common/character_enum.h"
#include "../../../game_engine/gui/basic/resource_pool.h"
#include "../character.h"

class Spaz: public Character {
public:
    Spaz(const std::shared_ptr<engine::ResourcePool>& resource_pool,
         const std::string& animation_name, int x, int y):
            Character(std::make_unique<engine::AnimatedSprite>(
                    resource_pool->get_texture(map_character_enum_to_string.at(SPAZ_CHARACTER)),
                    resource_pool->get_yaml(map_character_enum_to_string.at(SPAZ_CHARACTER)),
                    animation_name, x, y)) {}
};


#endif  // TP_FINAL_SPAZ_H
