
#include "enemy.h"

#include "../../../common/common_constants.h"

#include "player.h"

#define ATTACK_COOLDOWN 1000


//------- Overrided Methods --------

// These enemys for NOW can only move left and right, attack the player and cannot jump (for now)

Enemy::Enemy(size_t id, const character_t& character, int attack_damage, int health,
             int revive_cooldown, int x, int y, int w, int h, int speed):
        CharacterBody(id, character, x, y, w, h, Vector2D(speed, 0), health, STATE_IDLE_RIGHT,
                      revive_cooldown),
        attack_damage(attack_damage),
        attack_cooldown(ATTACK_COOLDOWN),
        x_speed(speed),
        spawn_position(x, y) {}

void Enemy::update_db() {

    if (!is_dead()) {
        position += velocity;
    }
}

void Enemy::handle_colision(CollisionObject* other) {

    Player* player = dynamic_cast<Player*>(other);

    if (player) {
        attack(player);
    }
}

//------- Movement Methods --------

void Enemy::attack(CharacterBody* player) {
    player->take_damage(this->attack_damage);
    player->knockback(10);
}

void Enemy::move_left() {
    direction = -1;
    velocity.x = -x_speed;
    state = STATE_MOVING_LEFT;
}

void Enemy::move_right() {
    direction = 1;
    velocity.x = x_speed;
    state = STATE_MOVING_RIGHT;
}

//------- Revive Methods --------

void Enemy::revive() {
    health = MAX_HEALTH * 0.75;
    set_state(STATE_IDLE_RIGHT);
    position = spawn_position;
}

//------- Movement Methods --------

void Enemy::update_status() {
    if (is_dead()) {
        if (can_revive()) {
            revive();
        } else {
            decrease_revive_cooldown();
        }
    }
    if (!is_dead() && get_health() == MIN_HEALTH) {
        velocity = Vector2D(0, 0);
        set_state(STATE_DEAD);
        reset_revive_cooldown();
    }
}

void Enemy::patrol(int match_time) {
    if (!is_dead()) {
        if (abs(match_time % 2) == 0) {
            if (is_facing_right()) {
                move_left();
            } else {
                move_right();
            }
        }
    }
}
