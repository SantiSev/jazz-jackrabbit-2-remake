#include "character.h"

#include <cstdint>
#include <utility>

#include "../../../common/character_enum.h"

CharacterBody::CharacterBody(size_t id, const character_t& character, int x, int y, int w, int h,
                             Vector2D velocity, size_t health, uint8_t state,
                             size_t revive_cooldown):
        DynamicBody(x, y, w, h, Vector2D(velocity)),
        id(id),
        health(health),
        character_reference(character),
        state(state),
        revive_cooldown(revive_cooldown) {}

//------- Getters --------

size_t CharacterBody::get_id() const { return id; }

size_t CharacterBody::get_health() const { return health; }

character_t CharacterBody::get_character() const { return character_reference; }

uint8_t CharacterBody::get_state() const { return state; }

bool CharacterBody::is_dead() const { return health == 0; }

//------- Setters --------

void CharacterBody::set_id(size_t new_id) { this->id = new_id; }

void CharacterBody::set_health(const size_t new_health) {
    this->health = new_health;
    if (new_health == 0)
        set_active_status(false);
}

void CharacterBody::set_character(const character_t& new_character) {
    this->character_reference = new_character;
}

void CharacterBody::set_state(const uint8_t new_state) { this->state = new_state; }

void CharacterBody::set_revival_cooldown(const size_t new_cooldown) {
    this->revive_cooldown = new_cooldown;
}

// ------- Health Methods --------

void CharacterBody::take_damage(size_t susbstract_health) {
    if (((int)health - (int)susbstract_health) < NONE) {
        set_active_status(false);
        health = NONE;
        state = STATE_DEAD;
    } else {
        health -= susbstract_health;
        state = STATE_DAMAGED;
    }
}

void CharacterBody::increase_health(size_t add_health) {
    if (((int)this->health + (int)add_health) > MAX_HEALTH) {
        this->health = MAX_HEALTH;
    } else {
        this->health += add_health;
    }
}

// ------- Revive Methods --------

void CharacterBody::decrease_revive_cooldown() { this->revive_cooldown--; }

bool CharacterBody::can_revive() const { return (is_active_object() && revive_cooldown == NONE); }

void CharacterBody::reset_revive_cooldown() { this->revive_cooldown = REVIVE_COOLDOWN; }


// ------- Movement Methods --------

bool CharacterBody::is_on_floor() const { return on_floor; }

bool CharacterBody::is_facing_right() const { return direction == RIGHT_DIR; }

int CharacterBody::get_direction() const { return direction; }

bool CharacterBody::is_doing_action_state() const {
    return (state == STATE_SHOOTING_LEFT || state == STATE_SHOOTING_RIGHT ||
            state == STATE_SPECIAL_RIGHT || state == STATE_SPECIAL_LEFT);
}

void CharacterBody::move_left() {
    direction = -1;
    velocity.x = -DEFAULT_SPEED_X;
    state = STATE_MOVING_LEFT;
}

void CharacterBody::move_right() {
    direction = 1;
    velocity.x = DEFAULT_SPEED_X;
    state = STATE_MOVING_RIGHT;
}

void CharacterBody::jump() {
    on_floor = false;
    velocity.y = -JUMP_SPEED;
    if (is_facing_right()) {
        state = STATE_JUMPING_RIGHT;
    } else {
        state = STATE_JUMPING_LEFT;
    }
}

void CharacterBody::knockback(int force) { velocity.x += -direction * force; }

void CharacterBody::update_body() {
    if (!on_floor) {
        velocity.y += GRAVITY;

    } else {
        velocity.x -= FRICCTION * direction;
    }

    position += velocity;
}

void CharacterBody::handle_colision(CollisionObject* other) {

    CollisionFace face = is_touching(other);

    // cast to Collectable
    Collectable* collectable = dynamic_cast<Collectable*>(other);

    if (!collectable) {  // if its a collectable, i want to go through it without stopping my
                         // movement

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
        } else if (face == CollisionFace::NO_COLLISION) {
            on_floor = false;
        }
    }
}