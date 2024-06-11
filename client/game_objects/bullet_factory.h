#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include <memory>
#include <string>

#include "../../common/character_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "./bullets/common_bullet.h"

class BulletFactory {
public:
    static std::unique_ptr<engine::AnimatedSprite> create_bullet(
            const std::shared_ptr<engine::ResourcePool>& resource_pool, uint8_t bullet_type,
            uint8_t direction, int x, int y) {
        switch (bullet_type) {
            case COMMON_BULLET:
                return std::make_unique<CommonBullet>(resource_pool, direction, x, y);
                break;
            // case SPAZ_CHARACTER:
            //     return std::make_unique<Spaz>(resource_pool, animation_name, x, y);
            //     break;
            // case LORI_CHARACTER:
            //     return std::make_unique<Lori>(resource_pool, animation_name, x, y);
            //     break;
            default:
                throw std::invalid_argument("Invalid character enum");
        }
    }
};

#endif  // BULLET_FACTORY_H
