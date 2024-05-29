//
// Created by santi on 25/05/24.
//
#include "colision_box.h"

ColisionBox::ColisionBox(int width, int height):
        width(width),
        height(height),
        tl_corner(0, 0),
        tr_corner(width, 0),
        bl_corner(0, height),
        br_corner(width, height) {}

ColisionBox::ColisionBox(int x, int y, int width, int height):
        width(width),
        height(height),
        tl_corner(x, y),
        tr_corner(width + x, y),
        bl_corner(x, height + y),
        br_corner(x + width, y + height) {}

Vector2D ColisionBox::get_tl_corner() const { return tl_corner; }

Vector2D ColisionBox::get_tr_corner() const {
    return tr_corner;  // Corrected to return tr_corner
}

Vector2D ColisionBox::get_bl_corner() const { return bl_corner; }

Vector2D ColisionBox::get_br_corner() const { return br_corner; }

int ColisionBox::get_width() const { return width; }

int ColisionBox::get_height() const { return height; }

void ColisionBox::set_width(int new_width) {
    width = new_width;
    tr_corner.set_x(tl_corner.get_x() + width);
    br_corner.set_x(bl_corner.get_x() + width);
}

void ColisionBox::set_height(int new_height) {
    height = new_height;
    bl_corner.set_y(tl_corner.get_y() + height);
    br_corner.set_y(tr_corner.get_y() + height);
}

void ColisionBox::update_position(Vector2D new_position) {
    tl_corner.set_x(new_position.get_x());
    tl_corner.set_y(new_position.get_y());
    tr_corner.set_x(new_position.get_x() + width);
    tr_corner.set_y(new_position.get_y());
    bl_corner.set_x(new_position.get_x());
    bl_corner.set_y(new_position.get_y() + height);
    br_corner.set_x(new_position.get_x() + width);
    br_corner.set_y(new_position.get_y() + height);
}

bool ColisionBox::is_touching(const ColisionBox& other) const {
    return (tl_corner.get_x() < other.br_corner.get_x() &&
            tl_corner.get_y() < other.br_corner.get_y() &&
            tr_corner.get_x() > other.bl_corner.get_x() &&
            bl_corner.get_y() > other.tr_corner.get_y());
}