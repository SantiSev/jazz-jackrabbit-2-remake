
#ifndef GUNS_H
#define GUNS_H

#include "weapon.h"

class GunOne: public Weapon {
public:
    GunOne(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class GunTwo: public Weapon {
public:
    GunTwo(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class GunThree: public Weapon {
public:
    GunThree(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class DefaultGun: public Weapon {
public:
    DefaultGun(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
    void shoot() override;
};

#endif  // GUNS_H
