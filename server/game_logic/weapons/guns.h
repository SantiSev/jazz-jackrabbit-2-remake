

#include "weapon.h"

class GunOne: public Weapon {
public:
    GunOne(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class GunTwo: public Weapon {
public:
    GunTwo(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class GunThree: public Weapon {
public:
    GunThree(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
};

class DefaultGun: public Weapon {
public:
    DefaultGun(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager);
    void shoot() override;
};
