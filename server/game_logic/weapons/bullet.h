#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <iostream>
#include <memory>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

class Player;

class Bullet: public DynamicBody {
private:
    Player& player_owner;
    int bullet_damage = 1;
    size_t life_span = 25;
    size_t bullet_id = 0;

public:
    Bullet(Player& player_owner, const int& bullet_damage, const size_t& bullet_id);

    size_t get_life_span() const;

    size_t get_damage() const;

    void get_player_points(size_t points);

    void update_db() override;

    void handle_colision(CollisionObject* other) override;
};


#endif
