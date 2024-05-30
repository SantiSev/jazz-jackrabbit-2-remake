//
// Created by santi on 25/05/24.
//

#include "area_object.h"

#include <iostream>

AreaObject::AreaObject(int width, int height): ColisionObject(width, height) {}

void AreaObject::detect_colision(ColisionObject& other) {

    if (is_touching_bool(other)) {
        handle_colision(other);
    }
}

void AreaObject::handle_colision(ColisionObject& other) {
    std::cout << "Collision handled" << std::endl;
}
