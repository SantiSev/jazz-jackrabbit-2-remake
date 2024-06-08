#include "guns.h"

GunOne::GunOne(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}

GunTwo::GunTwo(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}

GunThree::GunThree(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}
