//
// Created by santi on 25/05/24.
//
#include "colision_object.h"

CollisionObject::CollisionObject(int hitbox_width, int hitbox_height):
        GameObject(0, 0), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

CollisionObject::CollisionObject(int x, int y, int hitbox_width, int hitbox_height):
        GameObject(x, y), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

int CollisionObject::get_left_hitbox_side() const { return position.x; }

int CollisionObject::get_right_hitbox_side() const { return position.x + hitbox_width; }

int CollisionObject::get_top_hitbox_side() const { return position.y; }

int CollisionObject::get_bottom_hitbox_side() const { return position.y + hitbox_height; }

int CollisionObject::get_hitbox_width() const { return hitbox_width; }

int CollisionObject::get_hitbox_height() const { return hitbox_height; }

void CollisionObject::set_hitbox_width(int new_hitbox_width) { hitbox_width = new_hitbox_width; }

void CollisionObject::set_hitbox_height(int new_hitbox_height) {
    hitbox_height = new_hitbox_height;
}

bool CollisionObject::is_touching_bool(const CollisionObject& other) const {

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


CollisionFace CollisionObject::is_touching(const CollisionObject& other) const {

    /*
    Result:
        CollisionFace::LEFT: The right side of this is touching the left side of other.
        CollisionFace::RIGHT: The left side of this is touching the right side of other.
        CollisionFace::TOP: The bottom side of this is touching the top side of other.
        CollisionFace::BOTTOM: The top side of this is touching the bottom side of other.
        CollisionFace::NONE: No sides are touching.
    */

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
