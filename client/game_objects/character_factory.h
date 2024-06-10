#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>
#include <string>

#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "./enemies/lizard_goon.h"
#include "./enemies/mad_hatter.h"
#include "./players/jazz.h"
#include "./players/lori.h"
#include "./players/spaz.h"

class CharacterFactory {
public:
    static std::unique_ptr<Character> create_character(
            const std::shared_ptr<engine::ResourcePool>& resource_pool, character_t character_enum,
            const std::string& animation_name, int x, int y) {
        switch (character_enum) {
            case JAZZ_CHARACTER:
                return std::make_unique<Jazz>(resource_pool, animation_name, x, y);
                break;
            case SPAZ_CHARACTER:
                return std::make_unique<Spaz>(resource_pool, animation_name, x, y);
                break;
            case LORI_CHARACTER:
                return std::make_unique<Lori>(resource_pool, animation_name, x, y);
                break;
                // case LIZARD_GOON_CHARACTER:
                //     return std::make_unique<LizardGoon>(resource_pool, animation_name, x, y);
                //     break;
                // case MAD_HATTER_CHARACTER:
                //     return std::make_unique<MadHatter>(resource_pool, animation_name, x, y);
                //     break;
            default:
                throw std::invalid_argument("Invalid character enum");
        }
    }
};

#endif  // CHARACTER_FACTORY_H
