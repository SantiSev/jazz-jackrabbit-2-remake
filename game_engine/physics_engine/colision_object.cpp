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

    // Determine the sides of the current object
    int left = get_left_hitbox_side();
    int right = get_right_hitbox_side();
    int top = get_top_hitbox_side();
    int bottom = get_bottom_hitbox_side();

    // Determine the sides of the other object
    int other_left = other.get_left_hitbox_side();
    int other_right = other.get_right_hitbox_side();
    int other_top = other.get_top_hitbox_side();
    int other_bottom = other.get_bottom_hitbox_side();

    // Check for collision and determine the face being touched

    if (bottom >= other_top && top < other_top && right > other_left && left < other_right) {
        return CollisionFace::BOTTOM;  // Bottom face is touching the top face of the other object
    }
    if (top <= other_bottom && bottom > other_bottom && right > other_left && left < other_right) {
        return CollisionFace::TOP;  // Top face is touching the bottom face of the other object
    }
    if (right >= other_left && left < other_left && bottom > other_top && top < other_bottom) {
        return CollisionFace::RIGHT;  // Right face is touching the left face of the other object
    }
    if (left <= other_right && right > other_right && bottom > other_top && top < other_bottom) {
        return CollisionFace::LEFT;  // Left face is touching the right face of the other object
    }
    // If no collision is detected
    return CollisionFace::NONE;
}
