#include "enemy.h"

#include "../areaObjects/bullet.h"

Enemy::Enemy(const uint8_t& enemy_type, const size_t& id, int x, int y):
        DynamicBody(x, y, ENEMY_WIDTH, ENEMY_HEIGHT),
        id(id),
        state(STATE_IDLE_RIGHT),
        enemy_type(enemy_type) {}

size_t Enemy::get_id() const { return id; }

size_t Enemy::get_health() const { return health; }

bool Enemy::is_enemy_alive() const { return is_alive; }

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
    set_state(STATE_IDLE_RIGHT);
    position = spawn_position;
    is_alive = true;
}

bool Enemy::can_revive() const { return (revive_cooldown == 0 && !is_enemy_alive()); }

void Enemy::decrease_revive_cooldown() { revive_cooldown--; }

void Enemy::reset_revive_cooldown() { revive_cooldown = REVIVE_COOLDOWN; }

void Enemy::shoot() {}

void Enemy::kill() {
    velocity = Vector2D(0, 0);
    is_alive = false;
}

void Enemy::set_state(const uint8_t new_state) { this->state = new_state; }

void Enemy::set_spawn_point(const Vector2D& new_spawn_point) { spawn_position = new_spawn_point; }

Vector2D Enemy::get_spawn_point() { return spawn_position; }

void Enemy::move_left() {
    direction = -1;
    velocity.x = -DEFAULT_SPEED_X;
}

void Enemy::move_right() {
    direction = 1;
    velocity.x = DEFAULT_SPEED_X;
}

void Enemy::jump() {
    on_floor = false;
    velocity.y = -JUMP_SPEED;
}

void Enemy::update_db() {
    if (!on_floor) {
        velocity.y += GRAVITY;
    }
    position += velocity;

    // print_info(); TODO SACAR
}

bool Enemy::is_on_floor() const { return on_floor; }

bool Enemy::is_facing_right() const { return direction == 1; }

void Enemy::handle_colision(CollisionObject& other) {
    if (is_touching_bool(other)) {
        velocity.y = 10;
        on_floor = true;
    }
}

void Enemy::handle_impact(Bullet& bullet) {
    decrease_health(bullet.get_damage());
    if (health == 0) {
        bullet.get_player_points(ENEMY_KILL_POINTS);
    }
}

uint8_t Enemy::get_enemy_type() const { return enemy_type; }

uint8_t Enemy::get_state() const { return state; }
