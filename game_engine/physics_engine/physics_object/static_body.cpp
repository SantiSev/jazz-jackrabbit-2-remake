//
// Created by santi on 24/05/24.
//

#include "static_body.h"


StaticBody::StaticBody(int width, int height): CollisionObject(width, height) {}

StaticBody::StaticBody(int x, int y, int width, int height): CollisionObject(x, y, width, height) {}


void StaticBody::handle_colision(CollisionObject& other) {
    // This is a static body, so it does not move.
    // Therefore, it does not need to handle colisions.
    CollisionFace face = this->is_touching(other);

    // cast to dynamic_body

    switch (face) {
        case CollisionFace::TOP:

            other.position = Vector2D(other.position.x, position.y + get_hitbox_height());
            break;
        case CollisionFace::LEFT:  // other object is on the left of this object
                                   // Move other object to be just to the left of this object
            other.position = Vector2D(position.x + get_hitbox_width(), other.position.y);
            break;
        case CollisionFace::RIGHT:  // other object is on the right of this object
                                    // Move other object to be just to the right of this object

            other.position = Vector2D(position.x - other.get_hitbox_width(), other.position.y);
            break;
        case CollisionFace::BOTTOM:

            other.position = Vector2D(other.position.x, position.y - other.get_hitbox_height());
            other.handle_colision(*this);
            break;
        default:
            // No collision detected
            break;
    }
}
