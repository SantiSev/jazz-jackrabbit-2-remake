//
// Created by santi on 25/05/24.
//
#include "colision_object.h"

ColisionObject::ColisionObject(int hitbox_width, int hitbox_height):
        GameObject(0, 0), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

ColisionObject::ColisionObject(int x, int y, int hitbox_width, int hitbox_height):
        GameObject(x, y), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

int ColisionObject::get_left_hitbox_side() const { return get_position().get_x(); }

int ColisionObject::get_right_hitbox_side() const { return get_position().get_x() + hitbox_width; }

int ColisionObject::get_top_hitbox_side() const { return get_position().get_y(); }

int ColisionObject::get_bottom_hitbox_side() const {
    return get_position().get_y() + hitbox_height;
}

int ColisionObject::get_hitbox_width() const { return hitbox_width; }

int ColisionObject::get_hitbox_height() const { return hitbox_height; }

void ColisionObject::set_hitbox_width(int new_hitbox_width) { hitbox_width = new_hitbox_width; }

void ColisionObject::set_hitbox_height(int new_hitbox_height) { hitbox_height = new_hitbox_height; }

bool ColisionObject::is_touching_bool(const ColisionObject& other) const {

    int left_diff = get_right_hitbox_side() - other.get_left_hitbox_side();
    int right_diff = other.get_right_hitbox_side() - get_left_hitbox_side();
    int top_diff = get_bottom_hitbox_side() - other.get_top_hitbox_side();
    int bottom_diff = other.get_bottom_hitbox_side() - get_top_hitbox_side();

    bool touching_left = left_diff > 0 && left_diff <= get_hitbox_width();
    bool touching_right = right_diff > 0 && right_diff <= other.get_hitbox_width();
    bool touching_top = top_diff > 0 && top_diff <= get_hitbox_height();
    bool touching_bottom = bottom_diff > 0 && bottom_diff <= other.get_hitbox_height();

    return touching_left || touching_right || touching_top || touching_bottom;
}


CollisionFace ColisionObject::is_touching(const ColisionObject& other) const {

    int left_diff = get_right_hitbox_side() - other.get_left_hitbox_side();
    int right_diff = other.get_right_hitbox_side() - get_left_hitbox_side();
    int top_diff = get_bottom_hitbox_side() - other.get_top_hitbox_side();
    int bottom_diff = other.get_bottom_hitbox_side() - get_top_hitbox_side();

    bool touching_left = left_diff > 0 && left_diff <= get_hitbox_width();
    bool touching_right = right_diff > 0 && right_diff <= other.get_hitbox_width();
    bool touching_top = top_diff > 0 && top_diff <= get_hitbox_height();
    bool touching_bottom = bottom_diff > 0 && bottom_diff <= other.get_hitbox_height();

    if (touching_left && left_diff < right_diff && left_diff < top_diff &&
        left_diff < bottom_diff) {
        return CollisionFace::LEFT;
    }
    if (touching_right && right_diff < left_diff && right_diff < top_diff &&
        right_diff < bottom_diff) {
        return CollisionFace::RIGHT;
    }
    if (touching_top && top_diff < left_diff && top_diff < right_diff && top_diff < bottom_diff) {
        return CollisionFace::TOP;
    }
    if (touching_bottom && bottom_diff < left_diff && bottom_diff < right_diff &&
        bottom_diff < top_diff) {
        return CollisionFace::BOTTOM;
    }

    return CollisionFace::NONE;
}
