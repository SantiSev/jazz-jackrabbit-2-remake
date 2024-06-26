
#include "static_body.h"

#include <iostream>

StaticBody::StaticBody(int width, int height): CollisionObject(width, height) {}

StaticBody::StaticBody(int x, int y, int width, int height): CollisionObject(x, y, width, height) {}


void StaticBody::handle_colision(CollisionObject* other) {

    CollisionFace face = this->is_touching(other);

    switch (face) {

        case CollisionFace::TOP:  // other object is on top of me

            other->position.y = get_top_hitbox_side() - other->get_hitbox_height();
            break;

        case CollisionFace::LEFT:  // other object is on my left side

            other->position.x = get_left_hitbox_side() - other->get_hitbox_width() - 32;
            break;

        case CollisionFace::RIGHT:  // other object is on the right of this object

            other->position.x = get_right_hitbox_side() + 32;
            break;

        case CollisionFace::BOTTOM:  // other object is below me
            other->position.y = get_bottom_hitbox_side();
            break;
        default:
            break;
    }
}

void StaticBody::disable_collision(CollisionFace face) {
    switch (face) {
        case CollisionFace::TOP:
            top_collision = false;
            break;
        case CollisionFace::LEFT:
            left_collision = false;
            break;
        case CollisionFace::RIGHT:
            right_collision = false;
            break;
        case CollisionFace::BOTTOM:
            bottom_collision = false;
            break;
        default:
            break;
    }
}
