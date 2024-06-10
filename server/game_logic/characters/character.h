#ifndef TP_FINAL_CHARACTER_H
#define TP_FINAL_CHARACTER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../../common/character_enum.h"
#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../collectables/collectable.h"

// Player config
#define NONE 0
#define MAX_HEALTH 100
#define REVIVE_COOLDOWN 1000
#define INTOXICATON_COOLDOWN 4
#define SPECIAL_COOLDOWN 3
#define DEFAULT_SPEED_Y 10
#define DEFAULT_SPEED_X 10
#define JUMP_SPEED 25
#define GRAVITY 1
#define FRICCTION 0.1f
#define LEFT_DIR -1
#define RIGHT_DIR 1

class CharacterBody: public DynamicBody {
protected:
    // game info
    size_t id;
    size_t health;
    character_t character_reference;
    uint8_t state = STATE_IDLE_RIGHT;  // estado del personaje TODO: cambiar a enum

    // game cooldowns
    int revive_cooldown;

    // movement logic
    bool on_floor = true;
    int direction = RIGHT_DIR;

public:
    CharacterBody(size_t id, const character_t& character, int x, int y, int w, int h,
                  Vector2D velocity, size_t health, uint8_t state, size_t revive_cooldown);


    //------- Overrided Methods --------

    void handle_colision(CollisionObject* other) override;
    void update_body() override;

    //------- Getters --------

    size_t get_id() const;
    size_t get_health() const;
    character_t get_character() const;
    uint8_t get_state() const;
    bool is_dead() const;

    //------- Health Methods --------

    virtual void take_damage(size_t susbstract_health);
    virtual void increase_health(size_t add_health);

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
