#include "player.h"

#include <cstdint>
#include <utility>

#include "../../areaObjects/bullet.h"

Player::Player(size_t id, std::string name, const character_t& character, int x, int y,
               CollisionManager& collision_manager):
        DynamicBody(x, y, PLAYER_WIDTH, PLAYER_HEIGHT, Vector2D(NO_SPEED, DEFAULT_SPEED_Y)),
        collision_manager(collision_manager),
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

character_t Player::get_character() const { return character; }

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


void Player::set_character(const character_t& new_character) { this->character = new_character; }

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

void Player::revive(Vector2D pos) {
    this->health = MAX_HEALTH;
    this->revive_cooldown = REVIVE_COOLDOWN;
    this->state = STATE_IDLE_RIGHT;
    position = pos;
    is_alive = true;
}

uint8_t Player::get_state() const { return state; }

bool Player::is_player_alive() const { return is_alive; }

void Player::kill_player() {
    is_alive = false;
    velocity.x = 0;
    velocity.y = 0;
}

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

    // print_info(); TODO SACAR
}

void Player::handle_colision(CollisionObject& other) {

    CollisionFace face = is_touching(other);

    if (face == CollisionFace::LEFT ||
        face == CollisionFace::RIGHT) {  // if im touching something on my side, then i cant move
                                         // into it
        velocity.x = 0;
    } else if (face == CollisionFace::TOP) {  // if i touch something on top, then i cant move into
                                              // it and i stop moving up
        velocity.y = 0;
    } else if (face == CollisionFace::BOTTOM) {
        position.y = other.get_bottom_hitbox_side();
        velocity.y = 10;  // set a small value to avoid getting stuck in the air while walking off
                          // platform
        on_floor = true;
    } else if (face == CollisionFace::NONE) {
        on_floor = false;
    }

    other.handle_colision(*this);
}

bool Player::is_on_floor() const { return on_floor; }

bool Player::is_facing_right() const { return direction == 1; }

int Player::get_direction() const { return direction; }

void Player::handle_impact(Bullet& bullet) {
    decrease_health(bullet.get_damage());
    if (health == 0) {
        bullet.get_player_points(PLAYER_KILL_POINTS);
    }
}

// Bullet Player::shoot() {
//     weapons[selected_weapon].shoot() {
//         Bullet bullet(*this);
//         return bullet;
//     }
// }

bool Player::is_doing_action_state() const {
    return (state == STATE_SHOOTING_LEFT || state == STATE_SHOOTING_RIGHT ||
            state == STATE_ESPECIAL_RIGHT || state == STATE_ESPECIAL_LEFT);
}
