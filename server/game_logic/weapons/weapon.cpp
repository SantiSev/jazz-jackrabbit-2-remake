

#include "weapon.h"

#include "../characters/player.h"

Weapon::Weapon(uint8_t weapon_id, Player& player_owner, CollisionManager& collision_manager,
               int ammo, int max_ammo, int weapon_damage, int shoot_rate, int bullet_speed,
               const std::shared_ptr<Configuration>& config):
        weapon_id(weapon_id),
        weapon_damage(weapon_damage),
        ammo(ammo),
        max_ammo(max_ammo),
        shoot_rate(shoot_rate),
        bullet_speed(bullet_speed),
        player_owner(player_owner),
        collision_manager(collision_manager) {}

//---------- Getters ---------

uint8_t Weapon::get_weapon_id() const { return weapon_id; }

int Weapon::get_ammo() const { return ammo; }

int Weapon::get_max_ammo() const { return max_ammo; }


// -------------- Methods --------------

void Weapon::add_ammo(int added_ammo) {
    this->ammo += added_ammo;
    if (ammo > max_ammo) {
        ammo = max_ammo;
    }
}

bool Weapon::is_weapon_empty() const { return ammo == 0; }

void Weapon::shoot() {

    if (is_weapon_empty() || !can_shoot) {
        return;
    }

    if (!infinite_ammo) {
        ammo--;
    }

    shoot_rate_counter = 0;

    uint64_t bullet_id = create_bullet_id();
    auto bullet = std::make_shared<Bullet>(bullet_id, weapon_id, player_owner, weapon_damage,
                                           bullet_speed, config);
    collision_manager.track_dynamic_body(bullet);
}

void Weapon::update_shoot_rate() {

    if (shoot_rate_counter == shoot_rate) {
        can_shoot = true;

    } else {
        can_shoot = false;
        shoot_rate_counter++;
    }
}

void Weapon::reset_ammo() {
    if (max_ammo <= 0) {
        max_ammo = 10;
    }
    ammo = max_ammo / RESET_FACTOR;
}

// -------------- Private Methods --------------

uint64_t Weapon::create_bullet_id() {
    uint16_t id_weapon = this->weapon_id;
    uint16_t player_id = this->player_owner.get_id();

    bullet_counter++;

    uint64_t bullet_id = 0;  // Initialize bullet_id

    // Shift and combine values
    bullet_id |= static_cast<uint64_t>(id_weapon) << 48;  // Shift weapon_id to the leftmost 16 bits
    bullet_id |= static_cast<uint64_t>(player_id) << 32;  // Shift player_id to the next 16 bits
    bullet_id |=
            static_cast<uint64_t>(bullet_counter);  // bullet_counter occupies the remaining bits

    return bullet_id;
}

void Weapon::change_infinite_ammo() {
    if (ammo == 0) {
        ammo = 1;
    }
    if (infinite_ammo && ammo == 1) {
        ammo = 0;
    }
    infinite_ammo = !infinite_ammo;
}

Weapon::~Weapon() = default;
