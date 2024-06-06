#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <memory>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"
#include "../../game_logic/characters/player.h"


class Bullet: public DynamicBody {
private:
    std::shared_ptr<Player>& player_owner;
    size_t life_span = 10;
    bool impacted = false;


public:
    explicit Bullet(std::shared_ptr<Player>& player_owner);

    void decrease_life_span();
    size_t get_life_span() const;

    void update_db() override;
    void handle_colision(CollisionObject& other) override;
};


#endif
