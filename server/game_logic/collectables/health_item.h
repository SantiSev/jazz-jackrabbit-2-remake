// create healthItem clss with ifdef and everything, ahve it be inhereted from collectable

#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "../characters/player.h"

#include "collectable.h"

class HealthItem: public Collectable {
private:
    int health_amount;

public:
    HealthItem(int health_amount, int x, int y, int hitbox_width, int hitbox_height,
               int appearance_time):
            Collectable(x, y, hitbox_width, hitbox_height, appearance_time),
            health_amount(health_amount) {}

    void handle_colision(CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (player) {
            player->increase_health(health_amount);
            has_been_collected();
        }
    }
    int get_health_amount() const { return health_amount; }
};

#endif  // HEALTH_ITEM_H
