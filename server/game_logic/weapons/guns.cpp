#include "guns.h"

/*
 * Little Damage
 * A lot of ammo
 * A lot of Shoot rate
 * Little Bullet speed
 */
GunOne::GunOne(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}

/*
 * A lot of Damage
 * Little ammo
 * Little Shoot rate
 * A lot of Bullet speed
 */
GunTwo::GunTwo(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}

/*
 * A lot of Damage
 * Little ammo
 * A lot of Shoot rate
 * A lot of Bullet speed
 */
GunThree::GunThree(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, 0, 0, 0, 0, player_owner, collision_manager) {}
