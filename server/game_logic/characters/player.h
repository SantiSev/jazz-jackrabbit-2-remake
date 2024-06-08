#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../weapons/guns.h"

#include "character.h"

class Player: public CharacterBody {
private:
    std::string name;
    size_t points;
    std::vector<Weapon> weapons;
    size_t selected_weapon = DEFAULT_WEAPON;
    CollisionManager& collision_manager;  // reference to the collision manager

    // game statuses
    bool is_intoxicated = false;

    // game cooldowns

    size_t special_cooldown = 0;
    size_t intoxication_cooldown = INTOXICATON_COOLDOWN;

public:
    Player(size_t id, std::string name, const uint8_t& character, int x, int y,
           CollisionManager& collision_manager);

    //------- Overrided Methods --------

    void update_db() override;
    void handle_colision(CollisionObject* other) override;

    //------- Getters --------

    size_t get_points();
    Weapon get_weapon(size_t weapon);
    std::string get_name();

    //------- Setters --------

    void set_name(std::string name);
    void set_starting_weapon();

    //------- Point Methods --------

    void add_points(size_t points);

    //------- Weapon Methods --------

    void select_next_weapon();
    void shoot_selected_weapon();
    void reload_weapon(size_t ammo, size_t weapon);

    //------- Intoxication Methods --------

    void reset_intoxication();
    bool is_player_intoxicated() const;
    void decrease_intoxication_cooldown();
    size_t get_intoxication_cooldown() const;

    //------- Special Attack Methods --------

    int get_special_cooldown();
    bool is_special_available() const;
    void decrease_special_attack_cooldown();
    void reset_special_attack();

    //------- Movement Methods --------

    virtual void do_special_attack() = 0;
    void move_left() override;
    void move_right() override;
    void jump() override;
};


#endif
