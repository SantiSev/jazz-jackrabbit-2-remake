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
#define MAX_HEALTH 1000
#define REVIVE_COOLDOWN 10
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
    size_t revive_cooldown;

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

    //------- Setters --------

    void set_id(size_t new_id);
    void set_health(size_t health);
    void set_character(const character_t& new_character);
    void set_state(uint8_t new_state);
    void set_revival_cooldown(size_t new_cooldown);

    //------- Health Methods --------

    void take_damage(size_t susbstract_health);
    void increase_health(size_t add_health);

    //------- Revive Methods --------

    void decrease_revive_cooldown();
    bool can_revive() const;
    void reset_revive_cooldown();

    //------- Movement Methods --------

    bool is_on_floor() const;
    bool is_facing_right() const;
    int get_direction() const;
    bool is_doing_action_state() const;

    void virtual move_left();
    void virtual move_right();
    void virtual jump();
    void virtual knockback(int force);

    void revive(Vector2D new_position);
};


#endif
