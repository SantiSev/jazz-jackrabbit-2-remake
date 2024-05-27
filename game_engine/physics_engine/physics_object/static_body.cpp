//
// Created by santi on 24/05/24.
//

#include "static_body.h"

#include <iostream>


StaticBody::StaticBody(int width, int height): ColisionObject(width, height) {}

void StaticBody::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        std::cout << "Static Colision detected!" << std::endl;
    }
}
