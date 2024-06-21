
#ifndef TREASURE_H
#define TREASURE_H

#include "../characters/player.h"

#include "collectable.h"

class Treasure: public Collectable {
private:
    int value = 100;

public:
    Treasure(uint16_t id, int value, int x, int y, int hitbox_width, int hitbox_height,
             item_t item_type, int appearance_time):
            Collectable(id, x, y, hitbox_width, hitbox_height, item_type, appearance_time),
            value(value) {}

    void handle_colision(CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (!is_collected() && player) {
            player->add_points(value);
            has_been_collected();
        }
    };
};


#endif  // TREASURE_H
