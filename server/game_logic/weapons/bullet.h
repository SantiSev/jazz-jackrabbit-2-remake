#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <iostream>
#include <memory>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"


#define BULLET_LIFE_SPAN 1000
#define OFFSET_BULLET_X 3
#define BULLET_POINTS 10
#define BULLET_BONUS_POINTS 50
#define GOING_LEFT 0x00
#define GOING_RIGHT 1

class Player;

class Bullet: public DynamicBody {
private:
    uint64_t id;
    uint8_t direction;
    uint8_t type;
    Player& player_owner;
    int bullet_damage = 1;
    int life_span = BULLET_LIFE_SPAN;

public:
    Bullet(const uint64_t& id, const uint8_t type, Player& player_owner, const int& bullet_damage);

    uint64_t get_id() const;

    uint8_t get_direction() const;

    uint8_t get_type() const;

    void update_body() override;

    void handle_colision(CollisionObject* other) override;

    void print_info() override;

    void handle_out_of_bounds() override;
};


#endif
