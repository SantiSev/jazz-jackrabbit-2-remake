#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <cstdint>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../common/protocol/common_dto.h"
#include "../../../common/sfx_enum.h"
#include "../../../game_engine/physics_engine/collision_manager.h"
#include "../weapons/guns.h"

#include "character.h"

#define GRAVITY 1
#define DYING 1
#define DYING_TIME 160
#define INTOXICATION_SLOWDOWN 0.5

class Weapon;

class Player: public CharacterBody {
private:
    std::string name;
    int points = 0;
    std::vector<std::unique_ptr<Weapon>> weapons;
    size_t selected_weapon = DEFAULT_WEAPON;
    engine::CollisionManager& collision_manager;
    bool is_knocked_back = false;
    bool is_intoxicated = false;
    int special_cooldown = 0;
    int intoxication_cooldown = INTOXICATON_COOLDOWN;
    int invincibility_cooldown = INVINCIBILITY_COOLDOWN;
    bool is_invincible = false;
    bool is_sprinting = false;
    int shooting_height;
    std::shared_ptr<Configuration> config;

    // Dying handling
    int dying_duration = DYING_TIME;

    // Cheats
    bool invincibility_cheat_active = false;

    // Configs
    bool is_sprint_allowed = true;

    void move_horizontal(int new_direction);
    void sprint();
    bool is_shooting();

public:
    Player(uint16_t id, std::string name, const character_t& character, int x, int y, int w, int h,
           int shooting_h, engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config);

    //------- Overrided Methods --------

    void update_body() override;
    void handle_colision(engine::CollisionObject* other) override;
    void knockback(int force) override;
    void print_info() override;
    void revive(Vector2D new_position) override;
    void take_damage(int damage) override;

    //------- Getters --------

    int get_points() const;
    int get_shooting_height() const;
    std::string get_name() const;
    std::vector<std::unique_ptr<Weapon>>& get_weapons() const;
    Weapon* get_weapon(size_t weapon) const;
    Weapon* get_selected_weapon() const;

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

    void start_intoxication();
    void handle_intoxication();
    void reset_intoxication();

    //------- Invincibility Methods --------

    void start_invincibility();
    void handle_invincibility();
    void reset_invincibility();

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

    void execute_command(command_t command);

    //------- Deconstructor --------

    ~Player() {
        for (auto& weapon: weapons) {
            weapon.reset();
        }
        weapons.clear();
    }

    void activate_cheat_command(cheat_command_t command);

    void change_invincibility_cheat();
};

#endif
