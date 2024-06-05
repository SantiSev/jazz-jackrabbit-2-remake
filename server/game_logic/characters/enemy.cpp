#include "enemy.h"


Enemy::Enemy(int width, int height, const uint8_t& enemy_type, const size_t& id):
        DynamicBody(width, height), id(id), state(STATE_IDLE_RIGHT), enemy_type(enemy_type) {}

size_t Enemy::get_id() const { return id; }

size_t Enemy::get_health() const { return health; }

bool Enemy::is_enemy_alive() const { return is_alive; }

bool Enemy::is_enemy_jumping() const { return is_jumping; }

bool Enemy::is_enemy_facing_to_the_right() const { return is_facing_right; }

void Enemy::set_id(size_t new_id) { this->id = new_id; }

void Enemy::set_health(size_t new_health) { this->health = new_health; }

void Enemy::decrease_health(size_t susbstract_health) {
    if (((int)health - (int)susbstract_health) < MIN_HEALTH) {
        health = MIN_HEALTH;
    } else {
        health -= susbstract_health;
    }
}

void Enemy::increase_health(size_t add_health) {
    if (((int)health + (int)add_health) > MAX_HEALTH) {
        health = MAX_HEALTH;
    } else {
        health += add_health;
    }
}

void Enemy::revive() {
    health = MAX_HEALTH * 0.75;
    is_alive = true;
}

bool Enemy::can_revive() const { return (revive_cooldown == 0 && !is_enemy_alive()); }

void Enemy::decrease_revive_cooldown() { revive_cooldown--; }

void Enemy::reset_revive_cooldown() { revive_cooldown = REVIVE_COOLDOWN; }

void Enemy::shoot() {}

void Enemy::move_left() {}

void Enemy::move_right() {}


void Enemy::jump() { is_jumping = true; }

void Enemy::kill() { is_alive = false; }

void Enemy::set_state(const uint8_t new_state) { this->state = new_state; }
