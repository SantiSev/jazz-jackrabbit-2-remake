#include "player.h"


Player::Player(uint16_t id, std::string name, const character_t& character, int x, int y,
               CollisionManager& collision_manager):
        CharacterBody(id, character, x, y, PLAYER_WIDTH, PLAYER_HEIGHT,
                      Vector2D(NONE, MAX_FALL_SPEED), MAX_HEALTH, STATE_IDLE_RIGHT,
                      REVIVE_COOLDOWN),
        name(std::move(name)),
        weapons(NUM_OF_WEAPONS),
        collision_manager(collision_manager) {
    set_starting_weapon();
}


// -------- Getters ---------

int Player::get_points() const { return points; }

Weapon* Player::get_weapon(size_t weapon) const { return weapons[weapon].get(); }

std::string Player::get_name() const { return name; }

//------------ Setters ----------

void Player::set_name(std::string new_name) { this->name = std::move(new_name); }

void Player::set_starting_weapon() {  // todo check if its needed to be in config
    // TODO fix this the id should not be passed as a parameter
    weapons[0] = std::make_unique<DefaultGun>(COMMON_BULLET, *this, collision_manager);
    weapons[1] = std::make_unique<GunOne>(BULLET_ONE, *this, collision_manager);
    weapons[2] = std::make_unique<GunTwo>(BULLET_TWO, *this, collision_manager);
    weapons[3] = std::make_unique<GunThree>(BULLET_THREE, *this, collision_manager);
}

// ------------ Point Methods --------------

void Player::add_points(int new_points) { this->points += new_points; }

// ------------ Weapon Methods --------------

void Player::reload_weapon(size_t weapon_id, int ammo_amount) {

    this->weapons[weapon_id]->add_ammo(ammo_amount);
}

void Player::shoot_selected_weapon() {

#ifdef LOG_VERBOSE
    std::cout << "| Player id: " << this->id << " | Player::shoot_selected_weapon() |" << std::endl;
#endif

    weapons[selected_weapon]->shoot();
    state = is_facing_right() ? STATE_SHOOTING_RIGHT : STATE_SHOOTING_LEFT;
}

void Player::select_next_weapon() { selected_weapon = (selected_weapon + 1) % weapons.size(); }


// ------------ Intoxication Methods --------------

bool Player::is_player_intoxicated() const { return is_intoxicated; }

void Player::reset_intoxication() { is_intoxicated = false; }

void Player::decrease_intoxication_cooldown() { intoxication_cooldown--; }

size_t Player::get_intoxication_cooldown() const { return intoxication_cooldown; }

// ------------ Special Attack Methods --------------

bool Player::is_special_available() const { return special_cooldown == 0; }

void Player::decrease_special_attack_cooldown() { special_cooldown--; }

void Player::reset_special_attack() { special_cooldown = SPECIAL_COOLDOWN; }

// ------------ Movement Methods --------------

void Player::move_left() {

#ifdef LOG_VERBOSE
    std::cout << "| Player id: " << this->id << " | Player::move_left() |" << std::endl;
#endif

    if (is_knocked_back) {
        return;
    }

    direction = -1;
    velocity.x = -DEFAULT_SPEED_X;
    if (is_on_floor()) {
        if (is_player_intoxicated()) {
            state = STATE_INTOXICATED_MOV_LEFT;
        } else {
            state = STATE_MOVING_LEFT;
        }
    }
}

void Player::move_right() {

#ifdef LOG_VERBOSE
    std::cout << "| Player id: " << this->id << " | Player::move_right() |" << std::endl;
#endif

    if (is_knocked_back) {
        return;
    }

    direction = 1;
    velocity.x = DEFAULT_SPEED_X;
    if (is_on_floor()) {
        if (is_player_intoxicated()) {
            state = STATE_INTOXICATED_MOV_RIGHT;
        } else {
            state = STATE_MOVING_RIGHT;
        }
    }
}

void Player::jump() {

#ifdef LOG_VERBOSE
    std::cout << "| Player id: " << this->id << " | Player::jump() |" << std::endl;
#endif

    if (on_floor) {
        on_floor = false;
        velocity.y = -JUMP_SPEED;
    }
    if (is_facing_right()) {
        state = STATE_JUMPING_RIGHT;
    } else {
        state = STATE_JUMPING_LEFT;
    }
}

void Player::do_special_attack() {
    if (is_special_available()) {
        // GENERAR PROYECTIL ESPECIAL
        reset_special_attack();
    }
}


// ------------ Override Methods --------------

void Player::update_body() {


    if (is_dead()) {  // if the player is dead, then it shouldnt move
        return;
    }

    if (!on_floor) {
        if (velocity.y < MAX_FALL_SPEED) {
            velocity.y += GRAVITY;
        }

    } else {
        velocity.x -= FRICCTION * direction;
    }

    if (is_knocked_back) {
        velocity.x += FRICCTION * direction;
        if (velocity.x == 0) {
            is_knocked_back = false;
        }
        state = STATE_DAMAGED;
    }

    for (auto& weapon: weapons) {
        weapon->update_shoot_rate();
    }

    position += velocity;
}

void Player::handle_colision(CollisionObject* other) {

    CollisionFace face = is_touching(other);

    Collectable* collectable = dynamic_cast<Collectable*>(other);
    Bullet* bullet = dynamic_cast<Bullet*>(other);

    if (!collectable && !bullet && face != CollisionFace::NO_COLLISION) {

        if (face == CollisionFace::TOP) {
            velocity.y = 10;
            on_floor = false;

        } else if (face == CollisionFace::BOTTOM) {

            velocity.y = 10;
            on_floor = true;
        }
    }
}

void Player::knockback(int force) {
    velocity.x = -direction * force;
    velocity.y = -force;
    on_floor = false;
    is_knocked_back = true;
}

void Player::revive(Vector2D new_position) {
    this->health = MAX_HEALTH;
    this->revive_cooldown = REVIVE_COOLDOWN;
    this->state = STATE_IDLE_RIGHT;
    position = new_position;

    for (auto& weapon: weapons) {
        weapon->reset_ammo();
    }
}

void Player::print_info() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Position: " << position.x << " , " << position.y << " |" << std::endl;
    std::cout << "| Velocity: " << velocity.x << " , " << velocity.y << " |" << std::endl;
    std::cout << "| Health: " << health << " |" << std::endl;
    std::cout << "| on_floor: " << on_floor << " |" << std::endl;
    std::cout << "| weapon: " << selected_weapon << " |" << std::endl;
    std::cout << "| ammo: " << weapons[selected_weapon]->get_ammo() << " |" << std::endl;
    std::cout << "| shoot status: " << weapons[selected_weapon]->shoot_ready() << " |" << std::endl;
    std::cout << "| shoot status: " << weapons[selected_weapon]->shoot_rate_status() << " |"
              << std::endl;
    std::cout << "| points: " << points << " |" << std::endl;
    std::cout << "| state: " << (int)get_state() << " |" << std::endl;
}

//------- Match Methods --------

void Player::execute_command(command_t command) {
    if (is_dead()) {
        return;
    }

    switch (command) {
        case MOVE_LEFT:
            move_left();
            break;
        case MOVE_RIGHT:
            move_right();
            break;
        case JUMP:
            jump();
            break;
        case SHOOT:
            std::cout << "SHOOT" << std::endl;
            shoot_selected_weapon();
            break;
        default:
            break;
    }
}

void Player::update_status(Vector2D spawn_point) {  // todo check if its needed

    if (is_dead()) {
        return;
    }

    if (is_player_intoxicated()) {
        decrease_intoxication_cooldown();
        if (get_intoxication_cooldown() == NONE) {
            reset_intoxication();
        }
    }
    if (!is_special_available()) {
        decrease_special_attack_cooldown();
    }
    if (!is_dead() && get_health() == NONE) {
        velocity = Vector2D(0, 0);
        state = STATE_DEAD;
    }
    if (is_on_floor() && (get_state() == STATE_FALLING)) {
        if (is_facing_right()) {
            state = STATE_IDLE_RIGHT;
        } else {
            state = STATE_IDLE_LEFT;
        }
    }
    if (!is_on_floor() && (velocity.y > NONE) && !is_doing_action_state()) {
        state = STATE_FALLING;
    }
    if (is_on_floor() && !is_doing_action_state()) {
        if (is_facing_right()) {
            state = STATE_IDLE_RIGHT;
        } else {
            state = STATE_IDLE_LEFT;
        }
    }
}
