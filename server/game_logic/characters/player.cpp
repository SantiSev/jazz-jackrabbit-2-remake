#include "player.h"

#include <cstdint>
#include <utility>

Player::Player(size_t id, std::string name, const uint8_t& character, int x, int y,
               CollisionManager& collision_manager):
        CharacterBody(id, character, x, y, PLAYER_WIDTH, PLAYER_HEIGHT,
                      Vector2D(NO_SPEED, DEFAULT_SPEED_Y), MAX_HEALTH, STATE_IDLE_RIGHT,
                      REVIVE_COOLDOWN),
        name(std::move(name)),
        points(STARTING_POINTS),
        weapons(NUM_OF_WEAPONS),
        collision_manager(collision_manager) {
    set_starting_weapon();
}

// -------- Getters ---------

size_t Player::get_points() { return points; }

Weapon Player::get_weapon(size_t weapon) { return weapons[weapon]; }

std::string Player::get_name() { return name; }

//------------ Setters ----------

void Player::set_name(std::string new_name) { this->name = std::move(new_name); }

void Player::set_starting_weapon() {  // todo check if its needed to be in config
    weapons.push_back(DefaultGun(0, *this, collision_manager));
    weapons.push_back(GunOne(1, *this, collision_manager));
    weapons.push_back(GunTwo(2, *this, collision_manager));
    weapons.push_back(GunThree(3, *this, collision_manager));
}

// ------------ Point Methods --------------

void Player::add_points(size_t new_points) { this->points += new_points; }

// ------------ Weapon Methods --------------

bool Player::is_player_intoxicated() const { return is_intoxicated; }


void Player::reload_weapon(size_t ammo_amount, size_t weapon_id) {
    this->weapons[weapon_id].add_ammo(ammo_amount);
}


void Player::shoot_selected_weapon() { weapons[selected_weapon].shoot(); }

void Player::select_next_weapon() {
    // iterates through the weapons and select the next one in a loop the size of the weapons vector
    selected_weapon = (selected_weapon + 1) % weapons.size();
}

// ------------ Intoxication Methods --------------

void Player::reset_intoxication() { is_intoxicated = false; }

void Player::decrease_intoxication_cooldown() { intoxication_cooldown--; }

size_t Player::get_intoxication_cooldown() const { return intoxication_cooldown; }

// ------------ Special Attack Methods --------------

bool Player::is_special_available() const { return special_cooldown == 0; }

void Player::decrease_special_attack_cooldown() { special_cooldown--; }

void Player::reset_special_attack() { special_cooldown = SPECIAL_COOLDOWN; }

void Player::do_special_attack() {
    if (is_special_available()) {
        // GENERAR PROYECTIL ESPECIAL
        reset_special_attack();
    }
}

// ------------ Movement Methods --------------

void Player::move_left() {
    direction = -1;
    velocity.x = -DEFAULT_SPEED_X;
}

void Player::move_right() {
    direction = 1;
    velocity.x = DEFAULT_SPEED_X;
}

void Player::jump() {
    on_floor = false;
    velocity.y = -JUMP_SPEED;
}

// ------------ Override Methods --------------

void Player::update_db() {
    if (!on_floor) {
        velocity.y += GRAVITY;

    } else {
        velocity.x -= FRICCTION * direction;
    }

    for (auto& weapon: weapons) {
        weapon.update_shoot_rate();
    }

    position += velocity;

    // print_info();
}

void Player::handle_colision(CollisionObject* other) {

    CollisionFace face = is_touching(*other);

    if (!other->is_area_object()) {  // if its not an area object, then it should be able to enter
                                     // the hitbox
        if (face == CollisionFace::LEFT ||
            face == CollisionFace::RIGHT) {  // if im touching something on my side, then i cant
            // move
            // into it
            velocity.x = 0;
        } else if (face ==
                   CollisionFace::TOP) {  // if i touch something on top, then i cant move into
            // it and i stop moving up
            velocity.y = 0;
        } else if (face == CollisionFace::BOTTOM) {
            velocity.y =
                    10;  // set a small value to avoid getting stuck in the air while walking off
            // platform
            on_floor = true;
        } else if (face == CollisionFace::NONE) {
            on_floor = false;
        }
    }
}
