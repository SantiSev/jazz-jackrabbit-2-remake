//
// Created by santi on 24/05/24.
//

#include "static_body.h"

StaticBody::StaticBody(int width, int height): ColisionObject(width, height) {}

void StaticBody::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        // todo when the object is colided, the other object should not move
    }
}
