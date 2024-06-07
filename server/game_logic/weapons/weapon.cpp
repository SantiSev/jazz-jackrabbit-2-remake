#include "weapon.h"

// create constructor
Weapon::Weapon(size_t weapon_id, size_t ammo, size_t max_ammo, int weapon_damage, int shoot_rate,
               Player& player_owner, CollisionManager& collision_manager):
        weapon_id(weapon_id),
        ammo(ammo),
        max_ammo(max_ammo),
        weapon_damage(weapon_damage),
        shoot_rate(shoot_rate),
        player_owner(player_owner),
        collision_manager(collision_manager) {}

//---------- Getters ---------

size_t Weapon::get_weapon_id() const { return weapon_id; }

size_t Weapon::get_ammo() const { return ammo; }

size_t Weapon::get_max_ammo() const { return max_ammo; }

//---------- Setters ----------

void Weapon::set_weapon_name(size_t name) { this->weapon_id = name; }

void Weapon::set_ammo(size_t new_ammo) { this->ammo = new_ammo; }

void Weapon::set_max_ammo(size_t new_max_ammo) { this->max_ammo = new_max_ammo; }

// -------------- Methods --------------

void Weapon::add_ammo(size_t added_ammo) {
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

    ammo--;

    // TODOD --> get list of bullets reference from player
    auto bullet = std::make_shared<Bullet>(player_owner, weapon_damage);
    collision_manager.track_dynamic_body(bullet);
}

void Weapon::update_shoot_rate() {
    shoot_rate_counter++;

    if (shoot_rate_counter == shoot_rate) {
        can_shoot = true;
        shoot_rate_counter = 0;
    }
}


Weapon::~Weapon() = default;
