
#ifndef AMMO_H
#define AMMO_H

#include "../characters/player.h"

#include "collectable.h"

class Ammo: public Collectable {
private:
    int weapon_id = 1;
    int amount = 10;

public:
    Ammo(uint16_t id, int weapon_id, int amount, int x, int y, int hitbox_width, int hitbox_height,
         item_t item_type, int appearance_time):
            Collectable(id, x, y, hitbox_width, hitbox_height, item_type, appearance_time),
            weapon_id(weapon_id),
            amount(amount) {}

    void handle_colision(engine::CollisionObject* other) override {

        Player* player = dynamic_cast<Player*>(other);

        if (!is_collected() && player) {
            player->reload_weapon(weapon_id, amount);
            has_been_collected();
        }
    }
    int get_weapon_id() const { return weapon_id; }
};

#endif  // AMMO_H
