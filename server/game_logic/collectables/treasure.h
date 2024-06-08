//
// Created by santi on 08/06/24.
//

#ifndef TREASURE_H
#define TREASURE_H

#include "../characters/player.h"

#include "collectable.h"


class Treasure: public Collectable {
private:
    int value;

public:
    Treasure(int value, int x, int y, int hitbox_width, int hitbox_height):
            Collectable(x, y, hitbox_width, hitbox_height), value(value) {}

    void handle_colision(CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (player) {
            player->add_points(value);
            has_been_collected();
        }
    };
};


#endif  // TREASURE_H
