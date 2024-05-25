//
// Created by santi on 25/05/24.
//
#include "colision_object.h"


ColisionObject::ColisionObject(float width, float height): colisionBox(width, height) {}

ColisionObject::ColisionObject(float x, float y, float width, float height):
        GameObject(x, y), colisionBox(x, y, width, height) {}

float ColisionObject::getWidth() { return colisionBox.get_width(); }

float ColisionObject::getHeight() { return colisionBox.get_height(); }

void ColisionObject::setPosition(Vector2D newPosition) {
    position = newPosition;
    colisionBox.update_position(newPosition);
}

bool ColisionObject::is_in_area(const ColisionObject& other) {
    return colisionBox.is_touching(other.colisionBox);
}
