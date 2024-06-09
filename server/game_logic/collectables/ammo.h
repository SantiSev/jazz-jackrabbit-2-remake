//
// Created by santi on 08/06/24.
//

#ifndef AMMO_H
#define AMMO_H

#include "../characters/player.h"

#include "collectable.h"

class Ammo: public Collectable {
private:
    int weapon_id;
    int amount;

public:
    Ammo(int weapon_id, int amount, int x, int y, int hitbox_width, int hitbox_height):
            Collectable(x, y, hitbox_width, hitbox_height), weapon_id(weapon_id), amount(amount) {}

    void handle_colision(CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);
        if (player) {
            player->reload_weapon(weapon_id, amount);
            has_been_collected();
        }
    }
    int get_weapon_id() const { return weapon_id; }
};


#endif  // AMMO_H
