#ifndef TP_FINAL_ENEMY_H
#define TP_FINAL_ENEMY_H

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "../../../common/common_constants.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "player/weapon.h"

#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0
#define REVIVE_COOLDOWN 5

class Enemy: public DynamicBody {
private:
    size_t id;
    size_t health = MAX_HEALTH * 0.75;
    uint8_t state;
    uint8_t enemy_type;
    bool is_alive = true;
    size_t revive_cooldown = REVIVE_COOLDOWN;
    Vector2D spawn_position = Vector2D(0, 0);

public:
    Enemy(const uint8_t& enemy_type, const size_t& id, int x, int y);

    void update_db() override;
    void handle_colision(CollisionObject& other) override;

    //--------Getters--------

    size_t get_id() const;
    size_t get_health() const;
    uint8_t get_enemy_type() const;
    uint8_t get_state() const;

    //-------Statuses--------

    bool is_enemy_alive() const;
    bool is_enemy_jumping() const;

    //--------Setters--------

    void set_id(size_t id);
    void set_health(size_t health);

    //--------Health Methods--------

    void decrease_health(size_t susbstract_health);
    void increase_health(size_t add_health);

    //--------Revive Methods--------

    void revive();
    bool can_revive() const;
    void decrease_revive_cooldown();
    void reset_revive_cooldown();

    //--------Weapon Methods--------

    void shoot();

    //--------Movement Methods--------

    void move_left();
    void move_right();
    void jump();

    // game logic
    bool on_floor = true;
    int direction = 1;

    //------- Game Logic Methods --------

    bool is_on_floor() const;
    bool is_facing_right() const;
    void kill_enemy();


    ~Enemy() override = default;

    void kill();

    void set_state(const uint8_t new_state);

    void set_spawn_point(const Vector2D& new_spawn_point);

    Vector2D get_spawn_point();

    void handle_impact(Bullet& bullet) override;
};


#endif
