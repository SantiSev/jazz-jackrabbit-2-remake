#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include <memory>
#include <string>

#include "../../common/sfx_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "./bullets/bullet_one.h"
#include "./bullets/bullet_three.h"
#include "./bullets/bullet_two.h"
#include "./bullets/common_bullet.h"

class BulletFactory {
public:
    static std::shared_ptr<engine::AnimatedSprite> create_bullet(
            const std::shared_ptr<engine::ResourcePool>& resource_pool, bullet_type_t bullet_type,
            uint8_t direction, int x, int y) {
        switch (bullet_type) {
            case COMMON_BULLET:
                return std::make_shared<CommonBullet>(resource_pool, direction, x, y);
                break;
            case BULLET_ONE:
                return std::make_shared<BulletOne>(resource_pool, direction, x, y);
                break;
            case BULLET_TWO:
                return std::make_shared<BulletTwo>(resource_pool, direction, x, y);
                break;
            case BULLET_THREE:
                return std::make_shared<BulletThree>(resource_pool, direction, x, y);
                break;
            default:
                throw std::invalid_argument("Invalid character enum");
        }
    }
};

#endif  // BULLET_FACTORY_H
