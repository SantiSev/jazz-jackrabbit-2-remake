#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

#include "weapon.h"

#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0
#define REVIVE_COOLDOWN 5


class Player {
private:
    // DynamicBody character_body; // Commented by Agus: No compile
    size_t id;
    std::string name;
    size_t health;
    uint8_t character;
    size_t points;
    uint8_t state;
    // bool is_facing_right; (?)
    bool is_alive = true;
    size_t revive_cooldown = REVIVE_COOLDOWN;
    std::vector<Weapon> weapons{};
    size_t selected_weapon = DEFAULT_WEAPON;

public:
    Player(size_t id, std::string name, const uint8_t& character);

    size_t get_id() const;
    Vector2D get_position() const;
    std::string get_name();
    size_t get_health() const;
    uint8_t get_character() const;
    size_t get_points() const;
    void set_id(size_t id);
    void set_name(std::string name);
    void set_health(size_t health);
    void set_character(uint8_t new_character);
    void add_points(size_t points);
    void increase_points(size_t new_points);
    void decrease_health(size_t susbstract_health);
    void increase_health(size_t add_health);
    void revive();
    void decrease_revive_cooldown();
    bool can_revive() const;
    void select_weapon(size_t weapon_number);
    void shoot_selected_weapon();
    void get_weapon_ammo(size_t ammo, size_t weapon);
    void reset_revive_cooldown();
    uint8_t get_state() const;
    void set_starting_weapon();
};


#endif