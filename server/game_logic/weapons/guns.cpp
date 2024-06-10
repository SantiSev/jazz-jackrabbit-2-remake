#include "guns.h"

#include <memory>

/*
Constructor for guns:

        ----- sent by constructor -----
        - weapon_id: id of the weapon
        - player_owner: player that owns the weapon
        - collision_manager: collision manager of the game

        ----- personal config -----
        - damage: damage of the weapon
        - ammo: ammo of the weapon
        - shoot_rate: rate of shooting of the weapon
        - bullet_speed: speed of the bullets of the weapon
*/

/*
 * Little Damage
 * A lot of ammo
 * A lot of Shoot rate
 * Little Bullet speed
 */
GunOne::GunOne(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 5, 100, 6000000, 100) {}

/*
 * A lot of Damage
 * Little ammo
 * Little Shoot rate
 * A lot of Bullet speed
 */
GunTwo::GunTwo(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 25, 25, 1200000, 150) {}

/*
 * A lot of Damage
 * Little ammo
 * A lot of Shoot rate
 * A lot of Bullet speed
 */
GunThree::GunThree(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 50, 10, 500000, 200) {}

/*
 * Default Gun
 * Little Damage
 * Infinite ammo
 * regular shoot rate
 */

DefaultGun::DefaultGun(size_t weapon_id, Player& player_owner, CollisionManager& collision_manager):
        Weapon(weapon_id, player_owner, collision_manager, 10, 0, 60000, 100) {}

void DefaultGun::shoot() {

    if (!can_shoot) {
        return;
    }

    // TODOD --> get list of bullets reference from player
    auto bullet = std::make_shared<Bullet>(player_owner, weapon_damage, 0);
    collision_manager.track_dynamic_body(bullet);
}
