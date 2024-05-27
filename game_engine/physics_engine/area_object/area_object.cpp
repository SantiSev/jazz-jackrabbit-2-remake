//
// Created by santi on 25/05/24.
//

#include "area_object.h"

AreaObject::AreaObject(int width, int height): ColisionObject(width, height) {}

void AreaObject::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        // TODO: Here there should be a signal or something indicating that the object received a
        // collision It should be indicated that it was 'collected or touched'
    }
}
