//
// Created by santi on 24/05/24.
//

#include "dynamic_body.h"

#include <iostream>

DynamicBody::DynamicBody(int width, int height): CollisionObject(width, height) {}

DynamicBody::DynamicBody(int x, int y, int width, int height):
        CollisionObject(x, y, width, height) {}

DynamicBody::DynamicBody(int x, int y, int width, int height, Vector2D base_speed):
        CollisionObject(x, y, width, height), velocity(base_speed) {}

void DynamicBody::update_db() {}

void DynamicBody::print_info() {
    // also print current time
    std::cout << "--------------------------------" << std::endl;
    std::cout << "| Position: " << position.x << " , " << position.y << " |" << std::endl;
    std::cout << "| Velocity: " << velocity.x << " , " << velocity.y << " |" << std::endl;
}

void DynamicBody::handle_colision(
        CollisionObject& other) {  // other players cant overlap with other players

    CollisionFace face = is_touching(other);
    switch (face) {
        case CollisionFace::TOP:  // other object is under this object
                                  // Move other object to be just below this object

            break;
        case CollisionFace::LEFT:  // other object is on the left of this object
                                   // Move other object to be just to the left of this object

            break;
        case CollisionFace::RIGHT:  // other object is on the right of this object
                                    // Move other object to be just to the right of this object

            break;
        case CollisionFace::BOTTOM:  // other object is above this object
                                     // Move other object to be just above this object

            break;
        default:
            // No collision detected
            break;
    }
}
