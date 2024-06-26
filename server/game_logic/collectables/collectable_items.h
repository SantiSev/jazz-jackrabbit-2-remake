
#ifndef COLLECTABLE_ITEM_H
#define COLLECTABLE_ITEM_H

#include <cstdlib>
#include <ctime>

#include "ammo.h"
#include "health_item.h"
#include "treasure.h"


class AmmoGunOne: public Ammo {
public:
    AmmoGunOne(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            Ammo(id, 1, 10, x, y, w, h, BULLET_ONE_ITEM, respawn_time) {}
};

class AmmoGunTwo: public Ammo {
public:
    AmmoGunTwo(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            Ammo(id, 2, 10, x, y, w, h, BULLET_TWO_ITEM, respawn_time) {}
};

class AmmoGunThree: public Ammo {
public:
    AmmoGunThree(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            Ammo(id, 3, 10, x, y, w, h, BULLET_THREE_ITEM, respawn_time) {}
};

class Coin: public Treasure {
public:
    Coin(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            Treasure(id, 5, x, y, w, h, COIN, respawn_time) {}
};

class Meat: public HealthItem {
public:
    Meat(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            HealthItem(id, 50, x, y, w, h, MEAT, respawn_time) {}
};

class Carrot: public Collectable {
public:
    Carrot(uint16_t id, int x, int y, int w, int h, const int& respawn_time):
            Collectable(id, x, y, w, h, CARROT, respawn_time) {}

    void handle_colision(CollisionObject* other) override {

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
