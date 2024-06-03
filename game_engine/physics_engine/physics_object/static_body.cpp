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
        case CollisionFace::TOP:  // other object is under this object
                                  // Move other object to be just below this object
            other.update_position(other.get_position().get_x(),
                                  get_position().get_y() - other.get_hitbox_height());
            break;
        case CollisionFace::LEFT:  // other object is on the left of this object
                                   // Move other object to be just to the left of this object
            other.update_position(get_position().get_x() + other.get_hitbox_width(),
                                  other.get_position().get_y());
            break;
        case CollisionFace::RIGHT:  // other object is on the right of this object
                                    // Move other object to be just to the right of this object
            other.update_position(get_position().get_x() - get_hitbox_width(),
                                  other.get_position().get_y());
            break;
        case CollisionFace::BOTTOM:  // other object is above this object
                                     // Move other object to be just above this object
            other.update_position(other.get_position().get_x(),
                                  get_position().get_y() + get_hitbox_height());
            break;
        default:
            // No collision detected
            break;
    }
}
