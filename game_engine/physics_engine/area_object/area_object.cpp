//
// Created by santi on 25/05/24.
//

#include "area_object.h"

#include <iostream>

AreaObject::AreaObject(int width, int height): ColisionObject(width, height) {}

void AreaObject::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        std::cout << "Item Colision detected!" << std::endl;
    }
}
