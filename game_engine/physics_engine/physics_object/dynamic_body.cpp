#include "dynamic_body.h"

#include <iostream>

using engine::DynamicBody;

DynamicBody::DynamicBody(int width, int height): engine::CollisionObject(width, height) {}

DynamicBody::DynamicBody(int x, int y, int width, int height):
        engine::CollisionObject(x, y, width, height) {}

DynamicBody::DynamicBody(int x, int y, int width, int height, Vector2D base_speed):
        engine::CollisionObject(x, y, width, height), velocity(base_speed) {}

void DynamicBody::update_body() {}

void DynamicBody::print_info() {
    // also print current time
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Position: " << position.x << " , " << position.y << " |" << std::endl;
    std::cout << "| Velocity: " << velocity.x << " , " << velocity.y << " |" << std::endl;
}

void DynamicBody::handle_colision(
        engine::CollisionObject* other) {  // other players cant overlap with other players

    CollisionFace face = is_touching(other);
    switch (face) {
        case CollisionFace::TOP:  // other object is on top of me
            other->position.y = get_top_hitbox_side() - other->get_hitbox_height();
            break;
        case CollisionFace::LEFT:  // other object is on my left side
            other->position.x = get_left_hitbox_side() - other->get_hitbox_width();
            break;
        case CollisionFace::RIGHT:  // other object is on the right of this object
            other->position.x = get_right_hitbox_side();
            break;
        case CollisionFace::BOTTOM:  // other object is below me
            other->position.y = get_bottom_hitbox_side();
            break;
        default:
            // No collision detected
            break;
    }
}
