#ifndef TP_FINAL_CHARACTER_H
#define TP_FINAL_CHARACTER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../../common/character_enum.h"
#include "../../../common/common_constants.h"
#include "../../../common/configuration.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../collectables/collectable.h"

// Player config
#define NONE 0
#define MAX_HEALTH 100
#define REVIVE_COOLDOWN 1000
#define INTOXICATON_COOLDOWN 600
#define SPECIAL_COOLDOWN 3
#define DEFAULT_SPEED_Y 10
#define DEFAULT_SPEED_X 15
#define JUMP_SPEED 25
#define GRAVITY 1
#define FRICCTION 0.1f
#define LEFT_DIR -1
#define RIGHT_DIR 1
#define REVIVE_COOLDOWN 1000
#define INVINCIBILITY_COOLDOWN 600

class CharacterBody: public DynamicBody {

protected:
    // dto info

    uint16_t id;
    character_t character_reference;
    state_t state = STATE_IDLE_RIGHT;

    // game logic info

    int health;
    int revive_cooldown;
    bool on_floor = true;
    int direction = RIGHT_DIR;
    int revive_counter = revive_cooldown;

public:
    CharacterBody(size_t id, const character_t& character, int x, int y, int w, int h,
                  Vector2D velocity, int health, state_t state, int revive_cooldown);


    //------- Overrided Methods --------

    void handle_colision(CollisionObject* other) override;
    void update_body() override;

    //------- Getters --------

    uint16_t get_id() const;
    character_t get_character() const;
    state_t get_state() const;
    int get_health() const;
    bool is_dead();

    //------- Health Methods --------

    virtual void take_damage(int damage);
    virtual void increase_health(int add_health);

    //------- Revive Methods --------

    virtual void revive(Vector2D new_position);
    bool try_revive();

    //------- Movement Methods --------

    bool is_on_floor() const;
    bool is_facing_right() const;
    int get_direction() const;
    bool is_doing_action_state() const;

    virtual void move_left();
    virtual void move_right();
    virtual void jump();
    virtual void knockback(int force);
};


#endif
