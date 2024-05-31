#include "player.h"

#include <cstdint>
#include <utility>

#include "../../../common/common_constants.h"

Player::Player(size_t id, std::string name, std::string character):
        id(id),
        name(std::move(name)),
        health(MAX_HEALTH),
        character(std::move(character)),
        points(STARTING_POINTS),
        state(STATE_IDLE_RIGHT) {
    set_starting_weapon();
}
void Player::set_starting_weapon() {
    weapons[DEFAULT_WEAPON].set_is_empty(false);
    weapons[DEFAULT_WEAPON].set_weapon_name(DEFAULT_WEAPON);
    weapons[DEFAULT_WEAPON].set_ammo(100);
    weapons[FIRST_WEAPON].set_is_empty(true);
    weapons[FIRST_WEAPON].set_weapon_name(FIRST_WEAPON);
    weapons[FIRST_WEAPON].set_ammo(0);
    weapons[SECOND_WEAPON].set_ammo(0);
    weapons[SECOND_WEAPON].set_is_empty(true);
    weapons[SECOND_WEAPON].set_weapon_name(SECOND_WEAPON);
    weapons[THIRD_WEAPON].set_ammo(0);
    weapons[THIRD_WEAPON].set_is_empty(true);
    weapons[THIRD_WEAPON].set_weapon_name(THIRD_WEAPON);
    weapons[THIRD_WEAPON].set_ammo(0);
}

size_t Player::get_id() const { return id; }

std::string Player::get_name() { return name; }

size_t Player::get_health() const { return health; }

std::string Player::get_character() { return character; }

size_t Player::get_points() const { return points; }

void Player::add_points(size_t new_points) { this->points += new_points; }

void Player::set_id(const size_t new_id) { this->id = new_id; }

void Player::set_name(std::string new_name) { this->name = std::move(new_name); }

void Player::set_health(const size_t new_health) { this->health = new_health; }

void Player::decrease_health(size_t susbstract_health) {
    if (((int)health - (int)susbstract_health) < MIN_HEALTH) {
        health = MIN_HEALTH;
    } else {
        health -= susbstract_health;
    }
}

void Player::increase_health(size_t add_health) {
    if (((int)this->health + (int)add_health) > MAX_HEALTH) {
        this->health = MAX_HEALTH;
    } else {
        this->health += add_health;
    }
}

void Player::set_character(std::string new_character) {
    this->character = std::move(new_character);
}


void Player::increase_points(size_t new_points) { this->points += new_points; }

void Player::decrease_revive_cooldown() { this->revive_cooldown--; }

void Player::reset_revive_cooldown() { this->revive_cooldown = REVIVE_COOLDOWN; }

void Player::get_weapon_ammo(size_t ammo, size_t weapon) {
    this->weapons[weapon].add_ammo(ammo);
    this->weapons[weapon].set_is_empty(false);
}

void Player::shoot_selected_weapon() {
    if (selected_weapon == DEFAULT_WEAPON) {
        // GENERAR PROYECTIL DEFAULT (no decrementa balas)
    }
    if (!weapons[selected_weapon].is_weapon_empty())
        this->weapons[selected_weapon].decrease_ammo();
    if (weapons[selected_weapon].get_ammo() == 0) {
        weapons[selected_weapon].set_is_empty(true);
    }
    // GENERAR PROYECTIL
}


void Player::select_weapon(size_t weapon_number) {
    if (!weapons[weapon_number].is_weapon_empty()) {
        this->selected_weapon = weapons[weapon_number].get_weapon_name();
    }
}

bool Player::can_revive() const { return (!is_alive && revive_cooldown == 0); }

void Player::revive() {
    this->health = MAX_HEALTH;
    this->revive_cooldown = REVIVE_COOLDOWN;
    this->state = STATE_IDLE_RIGHT;
    // posicionar en spawn
}

uint8_t Player::get_state() const { return state; }
