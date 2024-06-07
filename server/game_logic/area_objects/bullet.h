#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <memory>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../characters/player.h"

class Bullet: public DynamicBody {
private:
    Player& player_owner;
    int bullet_damage = 1;
    size_t life_span = 25;
    bool is_active = true;

public:
    explicit Bullet(Player& player_owner, int bullet_damage, int bullet_speed);

    size_t get_life_span() const;

    size_t get_damage() const;

    void get_player_points(size_t points);

    void update_db() override;

    void handle_colision(CollisionObject* other) override;
};


#endif
