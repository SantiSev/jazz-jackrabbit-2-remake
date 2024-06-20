#ifndef ITEM_FACTORY_H
#define ITEM_FACTORY_H

#include <memory>
#include <string>

#include "../../common/item_enum.h"
#include "../../game_engine/gui/basic/resource_pool.h"
#include "../../game_engine/gui/widgets/animated_sprite.h"
#include "./items/bullet_one.h"
#include "./items/bullet_three.h"
#include "./items/bullet_two.h"
#include "./items/carrot.h"
#include "./items/coin.h"
#include "./items/health_icon.h"
#include "./items/meat.h"

class ItemFactory {
public:
    static std::shared_ptr<engine::AnimatedSprite> create_item(
            const std::shared_ptr<engine::ResourcePool>& resource_pool, item_t item_enum, int x,
            int y) {
        switch (item_enum) {
            case BULLET_ONE_ITEM:
                return std::make_shared<BulletOneItem>(resource_pool, x, y);
                break;
            case BULLET_TWO_ITEM:
                return std::make_shared<BulletTwoItem>(resource_pool, x, y);
                break;
            case BULLET_THREE_ITEM:
                return std::make_shared<BulletThreeItem>(resource_pool, x, y);
                break;
            case CARROT:
                return std::make_shared<Carrot>(resource_pool, x, y);
                break;
            case MEAT:
                return std::make_shared<Meat>(resource_pool, x, y);
                break;
            case COIN:
                return std::make_shared<Coin>(resource_pool, x, y);
                break;
            case HEALTH_ICON:
                return std::make_shared<HealthIcon>(resource_pool, x, y);
                break;
            default:
                throw std::invalid_argument("in item factory:Invalid character enum");
        }
    }
};

#endif  // ITEM_FACTORY_H
