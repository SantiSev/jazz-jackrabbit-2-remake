#include "character.h"

#include <cstdint>
#include <utility>

#include "../../../common/character_enum.h"

CharacterBody::CharacterBody(size_t id, const character_t& character, int x, int y, int w, int h,
                             Vector2D velocity, int health, uint8_t state, size_t revive_cooldown):
        DynamicBody(x, y, w, h, Vector2D(velocity)),
        id(id),
        character_reference(character),
        state(state),
        health(health),
        revive_cooldown(revive_cooldown) {}

//------- Getters --------

uint16_t CharacterBody::get_id() const { return id; }

character_t CharacterBody::get_character() const { return character_reference; }

uint8_t CharacterBody::get_state() const { return state; }

int CharacterBody::get_health() const { return health; }

bool CharacterBody::is_dead() const { return health == 0; }

// ------- Health Methods --------

void CharacterBody::take_damage(int damage) {

    health -= damage;

    if (health < NONE) {
        health = NONE;
        state = STATE_DEAD;
        set_active_status(false);
    } else {
        state = STATE_DAMAGED;
    }
}

void CharacterBody::increase_health(int add_health) {

    health += add_health;

    if (health > MAX_HEALTH) {
        health = MAX_HEALTH;
    }
}

// ------- Revive Methods --------

bool CharacterBody::try_revive() {

    if (!is_dead()) {
        return false;
    }

    if (revive_cooldown == NONE && !is_active_object()) {
        set_active_status(true);
        return true;
    } else {
        this->revive_cooldown--;
        return false;
    }
}

void CharacterBody::revive(Vector2D new_position) {
    this->health = MAX_HEALTH;
    this->revive_cooldown = REVIVE_COOLDOWN;
    this->state = STATE_IDLE_RIGHT;
    position = new_position;
}

// ------- Movement Methods --------

bool CharacterBody::is_on_floor() const { return on_floor; }

bool CharacterBody::is_facing_right() const { return direction == RIGHT_DIR; }

int CharacterBody::get_direction() const { return direction; }

// Avoid adding falling animation   || Agus es un bo
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

        if (velocity.y > 0 && !is_doing_action_state()) {
            state = STATE_FALLING;
        } else {
            state = is_facing_right() ? STATE_JUMPING_RIGHT : STATE_JUMPING_LEFT;
        }

    } else {
        velocity.x -= FRICCTION * direction;
    }

    position += velocity;
}

void CharacterBody::handle_colision(CollisionObject* other) {

    CollisionFace face = is_touching(other);

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