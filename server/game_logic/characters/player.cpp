#include "player.h"


Player::Player(uint16_t id, std::string name, const character_t& character, int x, int y, int w,
               int h, int shooting_h, CollisionManager& collision_manager):
        CharacterBody(id, character, x, y, w, h, Vector2D(NONE, MAX_FALL_SPEED), MAX_HEALTH,
                      STATE_IDLE_RIGHT, REVIVE_COOLDOWN),
        name(std::move(name)),
        weapons(NUM_OF_WEAPONS),
        collision_manager(collision_manager),
        shooting_height(shooting_h) {
    set_starting_weapon();
}


// -------- Getters ---------
int Player::get_shooting_height() const { return shooting_height; }

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

    if (is_intoxicated) {
        return;
    }

    weapons[selected_weapon]->shoot();
    state = is_facing_right() ? STATE_SHOOTING_RIGHT : STATE_SHOOTING_LEFT;
}

void Player::select_next_weapon() { selected_weapon = (selected_weapon + 1) % weapons.size(); }


// ------------ Intoxication Methods --------------

void Player::start_intoxication() {
    is_intoxicated = true;
    is_invincible = false;
    intoxication_cooldown = INTOXICATON_COOLDOWN;
}

void Player::handle_intoxication() {
    if (is_intoxicated) {
        intoxication_cooldown--;
        if (intoxication_cooldown == NONE) {
            is_intoxicated = false;
        }
    }
}

// ------------ Invinvibility Methods --------------

void Player::start_invincibility() {
    is_invincible = true;
    is_intoxicated = false;
    invincibility_cooldown = INVINCIBILITY_COOLDOWN;
}

void Player::handle_invincibility() {
    if (is_invincible && !invincibility_cheat_active) {
        invincibility_cooldown--;
        if (invincibility_cooldown == NONE) {
            is_invincible = false;
        }
    }
}

// ------------ Special Attack Methods --------------

bool Player::is_special_available() const { return special_cooldown == 0; }

void Player::decrease_special_attack_cooldown() { special_cooldown--; }

void Player::reset_special_attack() { special_cooldown = SPECIAL_COOLDOWN; }

// ------------ Movement Methods --------------

void Player::move_horizontal(int new_direction) {
    if (is_knocked_back) {
        return;
    }
    direction = new_direction;

    if (is_sprinting && !is_intoxicated) {
        velocity.x = direction * DEFAULT_SPEED_X + (int)(DEFAULT_SPEED_X * 0.35);
    } else {
        velocity.x = direction * DEFAULT_SPEED_X;
    }

    if (on_floor) {

        if (is_intoxicated) {
            state = is_facing_right() ? STATE_INTOXICATED_MOV_RIGHT : STATE_INTOXICATED_MOV_LEFT;

        } else if (is_sprinting) {
            state = is_facing_right() ? STATE_MOVING_RIGHT :
                                        STATE_INTOXICATED_MOV_LEFT;  // TODO CAMBIAR CUANDO ESTÉ EL
                                                                     // SPRITE DE SPRINT
        } else {
            state = is_facing_right() ? STATE_MOVING_RIGHT : STATE_MOVING_LEFT;
        }
    }
}


void Player::sprint() { is_sprinting = !is_sprinting; }

void Player::move_left() { move_horizontal(-1); }

void Player::move_right() { move_horizontal(1); }

void Player::jump() {
    if (is_intoxicated) {
        return;
    }
    if (on_floor) {
        on_floor = false;
        velocity.y = -JUMP_SPEED;
        state = is_facing_right() ? STATE_JUMPING_RIGHT : STATE_JUMPING_LEFT;
    }
}

void Player::do_special_attack() {
    if (is_special_available()) {
        // GENERAR PROYECTIL ESPECIAL
        reset_special_attack();
    }
}


// Avoid adding falling animation
bool Player::is_shooting() {
    return (state == STATE_SHOOTING_LEFT || state == STATE_SHOOTING_RIGHT ||
            state == STATE_SPECIAL_RIGHT || state == STATE_SPECIAL_LEFT);
}

// ------------ Override Methods --------------

void Player::update_body() {

    if (is_dead()) {  // if the player is dead, then it shouldnt move
        velocity = Vector2D(NONE, NONE);
        return;
    }

    handle_intoxication();
    handle_invincibility();


    if (velocity.x == NONE && on_floor && !is_knocked_back && !is_shooting()) {

        if (is_intoxicated) {
            state = STATE_INTOXICATED_IDLE;
        } else {
            state = is_facing_right() ? STATE_IDLE_RIGHT : STATE_IDLE_LEFT;
        }
    }

    if (on_floor && (get_state() == STATE_FALLING)) {
        state = is_facing_right() ? STATE_IDLE_RIGHT : STATE_IDLE_LEFT;
    }


    if (!on_floor) {

        if (velocity.y < MAX_FALL_SPEED) {
            velocity.y += GRAVITY;
        }

        if (velocity.x != 0) {
            velocity.x = direction * DEFAULT_SPEED_X * AIR_FRICCTION;
        }

        if (!is_shooting()) {
            if (velocity.y > NONE) {
                state = STATE_FALLING;
            } else {
                state = is_facing_right() ? STATE_JUMPING_RIGHT : STATE_JUMPING_LEFT;
            }
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
    set_active_status(true);
    revive_counter = revive_cooldown;  // this is for unexpected respawn calls without try_respawn
    this->health = MAX_HEALTH;
    this->state = STATE_IDLE_RIGHT;
    position = new_position;
    velocity = Vector2D(NONE, DEFAULT_SPEED_Y);

    for (auto& weapon: weapons) {
        weapon->reset_ammo();
    }
}

void Player::take_damage(int damage) {

    if (!is_invincible) {
        health -= damage;
    }

    if (health < NONE) {
        health = NONE;
        state = STATE_DEAD;
        set_active_status(false);
        velocity = Vector2D(NONE, NONE);
    } else {
        state = STATE_DAMAGED;
    }
}

void Player::print_info() {
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Id: " << id << " |" << std::endl;
    std::cout << "| Character: " << (int)character_reference << " |" << std::endl;
    std::cout << "| size: (" << get_hitbox_width() << "," << get_hitbox_height() << ") |"
              << std::endl;
    std::cout << "| Position: " << position.x << " , " << position.y << " |" << std::endl;
    std::cout << "| Velocity: " << velocity.x << " , " << velocity.y << " |" << std::endl;
    std::cout << "| Direction: " << direction << " |" << std::endl;
    std::cout << "| Health: " << health << " |" << std::endl;
    std::cout << "| on_floor: " << on_floor << " |" << std::endl;
    std::cout << "| weapon: " << selected_weapon << " |" << std::endl;
    std::cout << "| ammo: " << weapons[selected_weapon]->get_ammo() << " |" << std::endl;
    std::cout << "| shoot status: " << weapons[selected_weapon]->shoot_ready() << " |" << std::endl;
    std::cout << "| shoot status: " << weapons[selected_weapon]->shoot_rate_status() << " |"
              << std::endl;
    std::cout << "| points: " << points << " |" << std::endl;
    std::cout << "| state: " << (int)get_state() << " |" << std::endl;
    std::cout << "| respawn time: " << revive_cooldown << " |" << std::endl;
    std::cout << "| respawn counter: " << revive_counter << " |" << std::endl;
    std::cout << "| intoxication cooldown: " << intoxication_cooldown << " |" << std::endl;
    std::cout << "| invincibility cooldown: " << invincibility_cooldown << " |" << std::endl;
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
        case SPRINT:
            if (is_sprint_allowed) {
                sprint();
            }
            break;
        case JUMP:
            jump();
            break;
        case SHOOT:
            shoot_selected_weapon();
            break;
        case CHANGE_WEAPON:
            select_next_weapon();
            break;
        default:
            break;
    }
}

void Player::activate_cheat_command(cheat_command_t command) {
    switch (command) {
        case CHEAT_MAX_AMMO:
            for (auto& weapon: weapons) {
                weapon->add_ammo(weapon->get_max_ammo());
            }
            break;
        case CHEAT_INFINITE_AMMO:
            for (auto& weapon: weapons) {
                weapon->change_infinite_ammo();
            }
            break;
        case CHEAT_MAX_HEALTH:
            health = MAX_HEALTH;
            break;
        case CHEAT_INVINCIBLE:
            change_invincibility_cheat();
            break;
        default:
            break;
    }
}


void Player::change_invincibility_cheat() {

    invincibility_cheat_active = !invincibility_cheat_active;

    is_invincible = invincibility_cheat_active;
}
