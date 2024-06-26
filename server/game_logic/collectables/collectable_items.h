
#ifndef COLLECTABLE_ITEM_H
#define COLLECTABLE_ITEM_H

#include <cstdlib>
#include <ctime>

#include "ammo.h"
#include "health_item.h"
#include "treasure.h"


class AmmoGunOne: public Ammo {
public:
    AmmoGunOne(uint16_t id, int x, int y, int w, int h):
            Ammo(id, 1, 10, x, y, w, h, BULLET_ONE_ITEM, 100) {}
};

class AmmoGunTwo: public Ammo {
public:
    AmmoGunTwo(uint16_t id, int x, int y, int w, int h):
            Ammo(id, 2, 10, x, y, w, h, BULLET_TWO_ITEM, 100) {}
};

class AmmoGunThree: public Ammo {
public:
    AmmoGunThree(uint16_t id, int x, int y, int w, int h):
            Ammo(id, 3, 10, x, y, w, h, BULLET_THREE_ITEM, 100) {}
};

class Coin: public Treasure {
public:
    Coin(uint16_t id, int x, int y, int w, int h): Treasure(id, 5, x, y, w, h, COIN, 100) {}
};

class Meat: public HealthItem {
public:
    Meat(uint16_t id, int x, int y, int w, int h): HealthItem(id, 50, x, y, w, h, MEAT, 100) {}
};

class Carrot: public Collectable {
public:
    Carrot(uint16_t id, int x, int y, int w, int h): Collectable(id, x, y, w, h, CARROT, 100) {}

    void handle_colision(engine::CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (!is_collected() && player) {

            int carrot_condition = rand() % 2;

            if (carrot_condition == 0) {
                player->start_intoxication();
            } else {
                player->start_invincibility();
            }
            has_been_collected();
        }
    };
};

#endif  // COLLECTABLE_ITEM_H
