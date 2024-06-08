#ifndef TP_FINAL_CHARACTER_H
#define TP_FINAL_CHARACTER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

class CharacterBody: public DynamicBody {
protected:
    // game info
    size_t id;
    size_t health;
    uint8_t character_reference;  // tipo de personaje TODO: cambiar a enum
    uint8_t state;                // estado del personaje TODO: cambiar a enum

    // game cooldowns
    size_t revive_cooldown;

    // movement logic
    bool on_floor = true;
    int direction = 1;

public:
    CharacterBody(size_t id, const uint8_t& character, int x, int y, int w, int h,
                  Vector2D velocity, size_t health, uint8_t state, size_t revive_cooldown);

    //------- Overrided Methods --------
    void handle_colision(CollisionObject* other) override;
    void update_db() override;

    //------- Getters --------

    size_t get_id() const;
    size_t get_health() const;
    uint8_t get_character() const;
    uint8_t get_state() const;
    bool is_alive() const;

    //------- Setters --------

    void set_id(size_t new_id);
    void set_health(size_t health);
    void set_character(uint8_t new_character);
    void set_state(uint8_t new_state);
    void set_revival_cooldown(size_t new_cooldown);

    //------- Health Methods --------

    void take_damage(size_t susbstract_health);
    void increase_health(size_t add_health);

    //------- Revive Methods --------

    void revive();
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
};


#endif
