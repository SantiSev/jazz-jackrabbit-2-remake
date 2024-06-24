#include "guns.h"

#include <memory>

/*
Constructor for guns:

        ----- sent by constructor -----
        - weapon_id: id of the weapon
        - player_owner: player that owns the weapon
        - collision_manager: collision manager of the game

        ----- personal config -----
        -uint8_t ammo,
        -uint8_t max_ammo,
        -int weapon_damage,
        -int shoot_rate
*/

/*
 * Little Damage
 * A lot of ammo
 * A lot of Shoot rate
 * Little Bullet speed
 */
GunOne::GunOne(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager,
               const std::shared_ptr<Configuration>& config):
        Weapon(weapon_id, player_owner, collision_manager, config->bullet_base_ammo * 10,
               config->bullet_base_max_ammo * 10, config->bullet_base_dmg,
               config->bullet_base_shoot_rate / 2, config->bullet_base_speed / 2, config) {}

/*
 * A lot of Damage
 * Little ammo
 * Little Shoot rate
 * A lot of Bullet speed
 */
GunTwo::GunTwo(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager,
               const std::shared_ptr<Configuration>& config):
        Weapon(weapon_id, player_owner, collision_manager, config->bullet_base_ammo,
               (int)(config->bullet_base_max_ammo * 1.5), config->bullet_base_dmg * 4,
               config->bullet_base_shoot_rate * 3, config->bullet_base_speed * 2, config) {}

/*
 * A lot of Damage
 * Medium ammo
 * A lot of Shoot rate
 * Slow Bullet speed
 */
GunThree::GunThree(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager,
                   const std::shared_ptr<Configuration>& config):
        Weapon(weapon_id, player_owner, collision_manager, config->bullet_base_ammo * 2,
               config->bullet_base_max_ammo * 3, config->bullet_base_dmg * 3,
               config->bullet_base_shoot_rate / 2, config->bullet_base_speed / 2, config) {}

/*
 * Default Gun
 * Little Damage
 * Infinite ammo
 * regular shoot rate
 * Normal Bullet speed
 */

DefaultGun::DefaultGun(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager,
                       const std::shared_ptr<Configuration>& config):
        Weapon(weapon_id, player_owner, collision_manager, 99, config->bullet_base_max_ammo,
               config->bullet_base_dmg * 2, config->bullet_base_shoot_rate,
               config->bullet_base_speed, config) {}

void DefaultGun::shoot() {

    if (!can_shoot) {
        return;
    }

    shoot_rate_counter = 0;
    uint64_t bullet_id = create_bullet_id();
    auto bullet = std::make_shared<Bullet>(bullet_id, weapon_id, player_owner, weapon_damage,
                                           bullet_speed, config->match_points_enemy,
                                           config->match_points_player);
    collision_manager.track_dynamic_body(bullet);
}
