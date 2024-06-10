#include "guns.h"

#include <memory>

/*
Constructor for guns:

        ----- sent by constructor -----
        - weapon_id: id of the weapon
        - player_owner: player that owns the weapon
        - collision_manager: collision manager of the game

        ----- personal config -----
        -size_t ammo,
        -size_t max_ammo,
        -int weapon_damage,
        -int shoot_rate
*/

/*
 * Little Damage
 * A lot of ammo
 * A lot of Shoot rate
 * Little Bullet speed
 */
GunOne::GunOne(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 5, 200, 60, 20) {}

/*
 * A lot of Damage
 * Little ammo
 * Little Shoot rate
 * A lot of Bullet speed
 */
GunTwo::GunTwo(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 25, 25, 10, 20) {}

/*
 * A lot of Damage
 * Little ammo
 * A lot of Shoot rate
 * A lot of Bullet speed
 */
GunThree::GunThree(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 50, 10, 60, 20) {}

/*
 * Default Gun
 * Little Damage
 * Infinite ammo
 * regular shoot rate
 */

DefaultGun::DefaultGun(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 10, 0, 60, 20) {}

void DefaultGun::shoot() {

    if (!can_shoot) {
        return;
    }
    shoot_rate_counter = 0;
    uint64_t bullet_id = create_bullet_id();
    // TODOD --> get list of bullets reference from player
    auto bullet = std::make_shared<Bullet>(bullet_id, player_owner, weapon_damage);
    collision_manager.track_dynamic_body(bullet);
}
