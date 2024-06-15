
#include "enemy.h"

#include "../../../common/common_constants.h"

#include "player.h"

#define ATTACK_COOLDOWN 1000


//------- Constructors --------

// These enemys for NOW can only move left and right, attack the player and cannot jump (for now)

Enemy::Enemy(uint16_t id, const character_t& character, int attack_damage, int health,
             int revive_cooldown, int x, int y, int w, int h, int speed):
        CharacterBody(id, character, x, y, w, h, Vector2D(speed, 0), health, STATE_MOVING_RIGHT,
                      revive_cooldown),
        attack_damage(attack_damage),
        attack_cooldown(ATTACK_COOLDOWN),
        x_speed(speed),
        spawn_position(x, y) {}

//------------ Overrided Methods ------------

void Enemy::update_body() {

    if (!is_dead()) {
        patrol();
        position += velocity;
    } else {
        velocity = Vector2D(0, 0);
        state = STATE_DEAD;
    }
}

void Enemy::handle_colision(CollisionObject* other) {

    Player* player = dynamic_cast<Player*>(other);
    CollisionFace face = is_touching(other);

    if (player && face != CollisionFace::NO_COLLISION) {
#ifdef LOG_VERBOSE
        std::cout << "Enemy collided with player" << std::endl;
#endif

        attack(player);

        switch (face) {

            case CollisionFace::TOP:  // other object is on top of me

                player->position.y = get_top_hitbox_side() - player->get_hitbox_height();
                break;

            case CollisionFace::LEFT:  // other object is on my left side


                player->position.x = get_left_hitbox_side() - player->get_hitbox_width();
                break;

            case CollisionFace::RIGHT:  // other object is on the right of this object

                player->position.x = get_right_hitbox_side();
                break;

            case CollisionFace::BOTTOM:  // other object is below me
                player->position.y = get_bottom_hitbox_side();
                break;
            default:
                break;
        }
    }
}

void Enemy::print_info() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Enemy: " << id << std::endl;
    std::cout << "| Position: " << position.x << " , " << position.y << " |" << std::endl;
    std::cout << "| Velocity: " << velocity.x << " , " << velocity.y << " |" << std::endl;
    std::cout << "| Health: " << health << " |" << std::endl;
    std::cout << "| Active: " << is_active_object() << " |" << std::endl;
    std::cout << "| Revive Cooldown: " << revive_cooldown << std::endl;
    std::cout << "| Spawn Position: " << spawn_position.x << " , " << spawn_position.y << std::endl;
}

//------- Movement Methods --------

void Enemy::attack(CharacterBody* player) {
    player->knockback(20);
    player->take_damage(this->attack_damage);
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

//------- Movement Methods --------

void Enemy::patrol() {
    // Calculate the absolute difference between the current position and the spawn position
    int diff = std::abs(position.x - spawn_position.x);

    // If the difference is greater than or equal to 10, the enemy has reached the end of its path
    if (diff >= movement_range) {
        // If the current position is less than the spawn position, move right, otherwise move left
        if (position.x < spawn_position.x) {
            direction = 1;
            state = STATE_MOVING_RIGHT;
            move_right();
        } else {
            direction = -1;
            state = STATE_MOVING_LEFT;
            move_left();
        }
    }
}
