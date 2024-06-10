#ifndef BULLET_H
#define BULLET_H


#include <cstring>
#include <iostream>
#include <memory>

#include "../../../game_engine/gui/canvas_object.h"
#include "../../../game_engine/gui/widgets/color_rect.h"
#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

class Player;

class Bullet: public DynamicBody, public engine::CanvasObject {
private:
    Player& player_owner;
    int bullet_damage = 1;
    size_t life_span = 25;
    size_t bullet_id = 0;

    engine::ColorRect color_rect;  // todo --> remove later


public:
    Bullet(Player& player_owner, const int& bullet_damage, const size_t& bullet_id);

    size_t get_life_span() const;

    size_t get_damage() const;

    void get_player_points(size_t points);

    void update_db() override;

    void handle_colision(CollisionObject* other) override;


    void draw(SDL_Renderer* renderer) override { color_rect.draw(renderer); }

    void set_position(int x, int y) override {}

    void update_color_rect() { color_rect.set_position(position.x, position.y); }

    bool is_intersecting(SDL_Point& point) const override { return false; }
    bool is_intersecting(SDL_Rect& rect) const override { return false; }
};


#endif
