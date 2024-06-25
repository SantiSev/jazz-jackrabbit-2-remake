
#include "enemy.h"

#include "../../../common/common_constants.h"

#include "player.h"

//------- Constructors --------

// These enemies for NOW can only move left and right, attack the player and cannot jump (for now)

Enemy::Enemy(uint16_t id, const character_t& character, int x, int y, int w, int h,
             const std::shared_ptr<Configuration>& config):
        CharacterBody(id, character, x, y, w, h,
                      Vector2D(config->enemy_speed, config->enemy_falling_speed),
                      config->enemy_health, STATE_MOVING_RIGHT, config->enemy_respawn_cool_down),
        attack_damage(config->enemy_damage),
        movement_range(config->enemy_move_rng),
        config(config),
        spawn_position(x, y) {
    set_random_speed(config->enemy_speed);
}


void Enemy::set_random_speed(int set_speed) {
    x_speed = set_speed > BASE_SPEED ?
                      std::rand() % (config->enemy_speed - BASE_SPEED + 1) + BASE_SPEED :
                      BASE_SPEED;
}

//------------ Overrided Methods ------------

void Enemy::update_body() {

    if (attack_cooldown > NONE) {
        attack_cooldown--;
    }

    if (!is_dead()) {
        velocity.y = config->enemy_falling_speed;
        patrol();
        position += velocity;
    } else {
        velocity = Vector2D(0, 0);
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

void Enemy::take_damage(int damage) {  // TODO ADD MORE STATES TO ENEMY
    health -= damage;
    if (health <= 0) {
        health = 0;
        set_active_status(false);
    }
}

void Enemy::revive(Vector2D new_position) {
    set_active_status(true);
    revive_counter = revive_cooldown;
    health = config->enemy_health;
    position = new_position;
    velocity = Vector2D(x_speed, DEFAULT_SPEED_Y);
    spawn_position = new_position;
    set_active_status(true);
}

void Enemy::print_info() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Enemy Id: " << id << std::endl;
    std::cout << "| Character: " << (int)character_reference << " |" << std::endl;
    std::cout << "| Position: (" << position.x << " , " << position.y << ") |" << std::endl;
    std::cout << "| Velocity: (" << velocity.x << " , " << velocity.y << ") |" << std::endl;
    std::cout << "| Health: " << health << " |" << std::endl;
    std::cout << "| Attack Damage: " << attack_damage << " |" << std::endl;
    std::cout << "| Attack Cooldown: " << attack_cooldown << " |" << std::endl;
    std::cout << "| Movement Range: " << movement_range << " |" << std::endl;
    std::cout << "| Active: " << is_active_object() << " |" << std::endl;
    std::cout << "| Revive Cooldown: " << revive_cooldown << std::endl;
    std::cout << "| Revive Counter: " << revive_counter << std::endl;
    std::cout << "| Spawn Position: " << spawn_position.x << " , " << spawn_position.y << std::endl;
}

//------- Movement Methods --------

void Enemy::attack(CharacterBody* player) {
    if (attack_cooldown <= 0) {
        player->knockback(direction * 20);
        player->take_damage(this->attack_damage);
        attack_cooldown = ATTACK_COOLDOWN;
    }
}

void Enemy::move_horizontal(int new_direction) {
    direction = new_direction;
    velocity.x = x_speed * new_direction;
    state = is_facing_right() ? STATE_MOVING_RIGHT : STATE_MOVING_LEFT;
}

void Enemy::move_left() { move_horizontal(LEFT_DIR); }

void Enemy::move_right() { move_horizontal(RIGHT_DIR); }

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
