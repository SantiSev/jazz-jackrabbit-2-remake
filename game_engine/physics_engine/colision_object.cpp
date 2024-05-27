//
// Created by santi on 25/05/24.
//
#include "colision_object/colision_object.h"


ColisionObject::ColisionObject(int width, int height): colisionBox(width, height) {}

ColisionObject::ColisionObject(int x, int y, int width, int height):
        GameObject(x, y), colisionBox(x, y, width, height) {}

int ColisionObject::getWidth() { return colisionBox.get_width(); }

int ColisionObject::getHeight() { return colisionBox.get_height(); }

void ColisionObject::setWidth(int width) { colisionBox.set_width(width); }

void ColisionObject::setHeight(int height) { colisionBox.set_height(height); }

void ColisionObject::setPosition(Vector2D newPosition) {
    position = newPosition;
    colisionBox.update_position(newPosition);
}

bool ColisionObject::is_in_area(const ColisionObject& other) {
    return colisionBox.is_touching(other.colisionBox);
}
