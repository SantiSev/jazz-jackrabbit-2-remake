
#ifndef HEALTH_ITEM_H
#define HEALTH_ITEM_H

#include "../characters/player.h"

#include "collectable.h"

class HealthItem: public Collectable {
private:
    int health_amount;

public:
    HealthItem(uint16_t id, int health_amount, int x, int y, int hitbox_width, int hitbox_height,
               item_t item_type, int appearance_time):
            Collectable(id, x, y, hitbox_width, hitbox_height, item_type, appearance_time),
            health_amount(health_amount) {}

    void handle_colision(engine::CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (player) {
            player->increase_health(health_amount);
            has_been_collected();
        }
    }
    int get_health_amount() const { return health_amount; }
};

#endif  // HEALTH_ITEM_H
