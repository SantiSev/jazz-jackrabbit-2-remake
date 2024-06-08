
#include "enemy.h"

#include "../../../common/common_constants.h"

#include "player.h"

#define ATTACK_COOLDOWN 1000


// These enemys for NOW can only move left and right, attack the player and cannot jump (for now)

Enemy::Enemy(size_t id, const uint8_t& character, int attack_damage, int health,
             int revive_cooldown, int x, int y, int w, int h, int speed):
        CharacterBody(id, character, x, y, w, h, Vector2D(speed, 0), health,
                      state = STATE_IDLE_RIGHT, revive_cooldown),
        attack_damage(attack_damage),
        attack_cooldown(ATTACK_COOLDOWN),
        x_speed(speed) {}

void Enemy::update_db() {

    if (is_alive) {
        position += velocity;
    }
}

void Enemy::handle_colision(CollisionObject* other) {

    Player* player = dynamic_cast<Player*>(other);

    if (player) {
        attack(player);
    }
}

void Enemy::attack(CharacterBody* player) {
    player->take_damage(this->attack_damage);
    player->knockback(10);
}

void Enemy::move_left() {
    direction = -1;
    velocity.x = -x_speed;
}

void Enemy::move_right() {
    direction = 1;
    velocity.x = x_speed;
}
