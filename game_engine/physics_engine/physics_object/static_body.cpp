//
// Created by santi on 24/05/24.
//

#include "static_body.h"


StaticBody::StaticBody(int width, int height): CollisionObject(width, height) {}

StaticBody::StaticBody(int x, int y, int width, int height): CollisionObject(x, y, width, height) {}


void StaticBody::handle_colision(CollisionObject* other) {
    // This is a static body, so it does not move.
    // Therefore, it does not need to handle colisions.
    CollisionFace face = this->is_touching(*other);

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
