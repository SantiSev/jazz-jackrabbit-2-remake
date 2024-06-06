#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <memory>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../characters/player/player.h"


class Bullet: public DynamicBody {
private:
    Player& player_owner;
    size_t life_span = 10;
    bool is_active = true;
    int bullet_damage = 1;
    uint8_t bullet_type = 0x00;


public:
    explicit Bullet(Player& player_owner);

    size_t get_life_span() const;

    void update_db() override;
    void handle_colision(CollisionObject& other) override;

    size_t get_damage() const;

    void get_player_points(size_t points);
};


#endif
