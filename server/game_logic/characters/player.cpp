#include "player.h"

#include <utility>

Player::Player(size_t id, std::string name, std::string character):
        id(id),
        name(std::move(name)),
        health(MAX_HEALTH),
        character(std::move(character)),
        points(STARTING_POINTS) {}

size_t Player::get_id() const { return id; }

std::string Player::get_name() { return name; }

size_t Player::get_health() const { return health; }

std::string Player::get_character() { return character; }

size_t Player::get_points() const { return points; }

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
    if (this->health > MAX_HEALTH) {
        this->health = MAX_HEALTH;
    } else {
        this->health += add_health;
    }
}

void Player::set_character(std::string new_character) {
    this->character = std::move(new_character);
}

void Player::set_points(size_t new_points) { this->points = new_points; }

void Player::increase_points(size_t new_points) { this->points += new_points; }
