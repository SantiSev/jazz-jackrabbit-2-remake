//
// Created by santi on 24/05/24.
//

#include "static_body.h"

StaticBody::StaticBody(float width, float height): ColisionObject(width, height) {}

void StaticBody::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        // todo move al otro objeto para que no este adentro del objecto estatico
    }
}
