#ifndef TP_FINAL_WEAPON_H
#define TP_FINAL_WEAPON_H

#include <cstdio>
#include <memory>

#include "../../../common/configuration.h"
#include "../../../game_engine/physics_engine/collision_manager.h"

#include "bullet.h"

#define RESET_FACTOR 3

class Player;
class CollisionManager;

class Weapon {
private:
    int bullet_counter = 0;
    bool infinite_ammo = false;

protected:
    uint8_t weapon_id = 0;
    int weapon_damage = 10;
    int ammo = 0;
    int max_ammo = 10;
    int shoot_rate = 10;
    int bullet_speed = 20;
    const std::shared_ptr<Configuration> config;
    Player& player_owner;
    engine::CollisionManager& collision_manager;  // the weapon creates bullets and sends them to the
                                          // collision manager

    int shoot_rate_counter = 0;
    bool can_shoot = true;

    uint64_t create_bullet_id();
    bool is_weapon_empty() const;

public:
    Weapon(uint8_t weapon_id, Player& player_owner, engine::CollisionManager& collision_manager, int ammo,
           int max_ammo, int weapon_damage, int shoot_rate, int bullet_speed,
           const std::shared_ptr<Configuration>& config);

    // ------- Getters --------

    uint8_t get_weapon_id() const;
    int get_max_ammo() const;
    int get_ammo() const;
    bool shoot_ready() const { return can_shoot; }
    int shoot_rate_status() const { return shoot_rate_counter; }

    // ------- Methods --------

    void update_shoot_rate();
    virtual void shoot();
    void add_ammo(int added_ammo);
    virtual void reset_ammo();
    void change_infinite_ammo();

    virtual ~Weapon();
};

#endif
