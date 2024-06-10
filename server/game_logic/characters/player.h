#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../common/protocol/common_dto.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../weapons/guns.h"

#include "character.h"

// player config
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50
#define MAX_FALL_SPEED 10

class Weapon;

class Player: public CharacterBody {
private:
    std::string name;
    int points = 0;
    std::vector<std::unique_ptr<Weapon>> weapons;
    size_t selected_weapon = DEFAULT_WEAPON;
    CollisionManager& collision_manager;
    bool is_knocked_back = false;
    bool is_intoxicated = false;
    size_t special_cooldown = 0;
    size_t intoxication_cooldown = INTOXICATON_COOLDOWN;

public:
    Player(uint16_t id, std::string name, const character_t& character, int x, int y,
           CollisionManager& collision_manager);

    //------- Overrided Methods --------

    void update_body() override;
    void handle_colision(CollisionObject* other) override;
    void knockback(int force) override;
    void print_info() override;
    void revive(Vector2D new_position) override;

    //------- Getters --------

    int get_points() const;
    std::string get_name() const;
    std::vector<std::unique_ptr<Weapon>>& get_weapons() const;
    Weapon* get_weapon(size_t weapon) const;

    //------- Setters --------

    void set_name(std::string name);
    void set_starting_weapon();

    //------- Point Methods --------

    void add_points(int points);

    //------- Weapon Methods --------

    void select_next_weapon();
    void shoot_selected_weapon();
    void reload_weapon(size_t weapon, int ammo);

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

    void move_left() override;
    void move_right() override;
    void jump() override;
    virtual void do_special_attack();


    //------- Match Methods --------

    void update_status(Vector2D spawn_point);
    void execute_command(command_t command);

    //------- Deconstructor --------

    ~Player() {
        for (auto& weapon: weapons) {
            weapon.reset();
        }
        weapons.clear();
    }
};

#endif
