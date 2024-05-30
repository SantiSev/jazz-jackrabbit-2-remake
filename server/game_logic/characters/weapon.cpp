#include "weapon.h"


void Weapon::set_weapon_name(size_t name) {
    this->weapon_name = name;
}

size_t Weapon::get_weapon_name() const { return weapon_name; }

void Weapon::set_ammo(size_t new_ammo) {
    this->ammo = new_ammo;
}
void Weapon::add_ammo(size_t added_ammo) {
    this->ammo += added_ammo;
}
size_t Weapon::get_ammo() const { return this->ammo; }

void Weapon::set_is_empty(bool is_weapon_empty) {
    this->is_empty = is_weapon_empty;
}
bool Weapon::is_weapon_empty() const { return is_empty; }

void Weapon::decrease_ammo() {
    this->ammo--;
}
Weapon::Weapon() = default;
Weapon::~Weapon() = default;
