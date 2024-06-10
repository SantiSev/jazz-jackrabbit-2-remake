//
// Created by santi on 08/06/24.
//

#ifndef AMMO_H
#define AMMO_H

#include "../characters/player.h"

#include "collectable.h"

class Ammo: public Collectable {
private:
    int weapon_id = 1;
    int amount = 10;

public:
    Ammo(int weapon_id, int amount, int x, int y, int hitbox_width, int hitbox_height,
         int appearance_time):
            Collectable(x, y, hitbox_width, hitbox_height, appearance_time),
            weapon_id(weapon_id),
            amount(amount) {}

    void handle_colision(CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);

        if (!is_collected() && player) {
            player->reload_weapon(amount, weapon_id);
            has_been_collected();
        }
    }
    int get_weapon_id() const { return weapon_id; }
};

#endif  // AMMO_H
