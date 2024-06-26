
#ifndef GUNS_H
#define GUNS_H

#include <memory>

#include "../../../common/configuration.h"

#include "weapon.h"

class GunOne: public Weapon {
public:
    GunOne(uint8_t weapon_id, Player& player_owner, engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config);
};

class GunTwo: public Weapon {
public:
    GunTwo(uint8_t weapon_id, Player& player_owner, engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config);
};

class GunThree: public Weapon {
public:
    GunThree(uint8_t weapon_id, Player& player_owner, engine::CollisionManager& collision_manager,
             const std::shared_ptr<Configuration>& config);
};

class DefaultGun: public Weapon {
public:
    DefaultGun(uint8_t weapon_id, Player& player_owner, engine::CollisionManager& collision_manager,
               const std::shared_ptr<Configuration>& config);
    void shoot() override;
    void reset_ammo() override;
};

#endif  // GUNS_H
