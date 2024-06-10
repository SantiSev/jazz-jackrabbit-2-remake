#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <iostream>
#include <memory>

#include "../../../game_engine/gui/canvas_object.h"
#include "../../../game_engine/gui/widgets/color_rect.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"


#define BULLET_LIFE_SPAN 1000
#define OFFSET_BULLET_X 3
#define BULLET_POINTS 10
#define BULLET_BONUS_POINTS 50
#define GOING_LEFT 0
#define GOING_RIGHT 1

class Player;

class Bullet: public DynamicBody, public engine::CanvasObject {
private:
    uint64_t id;
    uint8_t direction;
    uint8_t type;
    Player& player_owner;
    int bullet_damage = 1;
    int life_span = BULLET_LIFE_SPAN;

    engine::ColorRect color_rect;  // todo --> remove later

public:
    Bullet(const uint64_t& id, const uint8_t type, Player& player_owner, const int& bullet_damage);

    uint64_t get_id() const;

    uint8_t get_direction() const;

    uint8_t get_type() const;

    void update_body() override;

    void handle_colision(CollisionObject* other) override;

    // TODO --> REMOVE SDL LATER

    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    void set_position(int x, int y) override {}

    void update_color_rect() { color_rect.set_position(position.x, position.y); }

    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};


#endif
