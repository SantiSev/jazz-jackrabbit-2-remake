#ifndef TP_FINAL_WEAPON_H
#define TP_FINAL_WEAPON_H

#include <cstdio>
#include <memory>

#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/collision_manager.h"

#include "bullet.h"

class Player;
class CollisionManager;

class Weapon {
protected:
    size_t weapon_id = 0;
    int weapon_damage = 0;
    size_t ammo = 0;
    size_t max_ammo = 0;
    Player& player_owner;
    int shoot_rate = 10;
    CollisionManager& collision_manager;  // the weapon creates bullets and sends them to the
                                          // collision manager

    int shoot_rate_counter = 0;
    bool can_shoot = true;

    size_t get_max_ammo() const;

    void set_weapon_name(size_t weapon_name);
    void set_ammo(size_t new_ammo);
    void set_max_ammo(size_t new_max_ammo);

    bool is_weapon_empty() const;

public:
    Weapon(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager, size_t ammo,
           size_t max_ammo, int weapon_damage, int shoot_rate);

    void add_ammo(size_t added_ammo);

    size_t get_weapon_id() const;
    size_t get_ammo() const;

    // todo --> this is for testing purposes, remove later
    bool shoot_ready() const { return can_shoot; }
    int shoot_rate_status() const { return shoot_rate_counter; }

    void update_shoot_rate();

    virtual void shoot();

    ~Weapon();
};

#endif
