#ifndef TP_FINAL_ENEMY_H
#define TP_FINAL_ENEMY_H

#include <cstdlib>
#include <ctime>
#include <memory>

#include "character.h"

// Enemy config
#define ENEMY_WIDTH 35
#define ENEMY_HEIGHT 45
#define MOVEMENT_RANGE 50
#define ATTACK_COOLDOWN 60
#define BASE_SPEED 3

class Enemy: public CharacterBody {
private:
    int attack_damage;
    int attack_cooldown = 0;
    bool is_attacking = false;
    int x_speed;
    int movement_range;
    std::shared_ptr<Configuration> config;

    void move_horizontal(int new_direction);
    void set_random_speed(int set_speed);

public:
    Enemy(uint16_t id, const character_t& character, int x, int y, int w, int h,
          const std::shared_ptr<Configuration>& config);

    //------- Overrided Methods --------

    void update_body() override;
    void handle_colision(CollisionObject* other) override;
    void take_damage(int damage) override;
    void revive(Vector2D new_position) override;
    void print_info() override;

    //------- Movement Methods --------

    void attack(CharacterBody* player);
    void move_left() override;
    void move_right() override;

    //------- Game Methods --------
    Vector2D spawn_position;
    virtual void patrol();
};


#endif
