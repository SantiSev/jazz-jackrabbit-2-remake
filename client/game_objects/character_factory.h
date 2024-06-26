#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <memory>
#include <string>

#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "./enemies/lizard_goon.h"
#include "./enemies/mad_hatter.h"
#include "./players/jazz.h"
#include "./players/lori.h"
#include "./players/spaz.h"

class CharacterFactory {
public:
    static std::shared_ptr<engine::AnimatedSprite> create_character(
            const std::shared_ptr<engine::ResourcePool>& resource_pool, character_t character_enum,
            const std::string& animation_name, int x, int y) {
        switch (character_enum) {
            // Players
            case JAZZ_CHARACTER:
                return std::make_shared<Jazz>(resource_pool, animation_name, x, y);
                break;
            case SPAZ_CHARACTER:
                return std::make_shared<Spaz>(resource_pool, animation_name, x, y);
                break;
            case LORI_CHARACTER:
                return std::make_shared<Lori>(resource_pool, animation_name, x, y);
                break;

            // Enemies
            case LIZARD_GOON:
                return std::make_shared<LizardGoon>(resource_pool, animation_name, x, y);
                break;
            case MAD_HATTER:
                return std::make_shared<MadHatter>(resource_pool, animation_name, x, y);
                break;
            default:
                throw std::invalid_argument("in character factory:Invalid character enum");
        }
    }
};

#endif  // CHARACTER_FACTORY_H
