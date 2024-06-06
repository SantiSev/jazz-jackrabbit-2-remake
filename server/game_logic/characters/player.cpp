#include "player.h"

#include <cstdint>
#include <utility>

Player::Player(size_t id, std::string name, const uint8_t& character, int x, int y):
        DynamicBody(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(0, DEFAULT_SPEED_Y)),
        id(id),
        name(std::move(name)),
        health(MAX_HEALTH),
        character(character),
        points(STARTING_POINTS),
        state(STATE_IDLE_RIGHT),
        weapons(NUM_OF_WEAPONS) {
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

uint8_t Player::get_character() const { return character; }

size_t Player::get_points() const { return points; }

void Player::add_points(size_t new_points) { this->points += new_points; }

void Player::set_id(const size_t new_id) { this->id = new_id; }

void Player::set_name(std::string new_name) { this->name = std::move(new_name); }

void Player::set_health(const size_t new_health) { this->health = new_health; }

void Player::set_state(const uint8_t new_state) { this->state = new_state; }


bool Player::is_player_intoxicated() const { return is_intoxicated; }

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

void Player::set_character(uint8_t new_character) { this->character = new_character; }


void Player::increase_points(size_t new_points) { this->points += new_points; }

void Player::decrease_revive_cooldown() { this->revive_cooldown--; }

void Player::reset_revive_cooldown() { this->revive_cooldown = REVIVE_COOLDOWN; }

void Player::add_weapon_ammo(size_t ammo, size_t weapon) {
    this->weapons[weapon].add_ammo(ammo);
    this->weapons[weapon].set_is_empty(false);
}

Weapon Player::get_weapon(size_t weapon) { return weapons[weapon]; }

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

bool Player::is_player_alive() const { return is_alive; }

void Player::kill_player() { is_alive = false; }

void Player::reset_intoxication() { is_intoxicated = false; }

void Player::decrease_intoxication_cooldown() { intoxication_cooldown--; }

size_t Player::get_intoxication_cooldown() const { return intoxication_cooldown; }

bool Player::is_special_available() const { return special_cooldown == 0; }

void Player::decrease_special_attack_cooldown() { special_cooldown--; }

void Player::reset_special_attack() { special_cooldown = SPECIAL_COOLDOWN; }

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

void Player::update_db() {
    if (!on_floor) {
        velocity.y += GRAVITY;

    } else {
        velocity.x -= FRICCTION * direction;
    }

    position += velocity;

    print_info();
}

bool Player::is_on_floor() const { return on_floor; }

bool Player::is_facing_right() const { return direction == 1; }
