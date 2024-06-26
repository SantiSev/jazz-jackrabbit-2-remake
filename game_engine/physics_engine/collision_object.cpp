
#include "collision_object.h"


using engine::CollisionObject;

CollisionObject::CollisionObject(int hitbox_width, int hitbox_height):
        position(0, 0), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

CollisionObject::CollisionObject(int x, int y, int hitbox_width, int hitbox_height):
        position(x, y), hitbox_width(hitbox_width), hitbox_height(hitbox_height) {}

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

bool CollisionObject::is_active_object() const { return is_active; }

void CollisionObject::set_active_status(bool status) { is_active = status; }


bool CollisionObject::is_touching_bool(const CollisionObject* other) const {

    if (other == nullptr) {
        return false;
    }

    int left_diff = get_right_hitbox_side() - other->get_left_hitbox_side();
    int right_diff = other->get_right_hitbox_side() - get_left_hitbox_side();
    int top_diff = get_bottom_hitbox_side() - other->get_top_hitbox_side();
    int bottom_diff = other->get_bottom_hitbox_side() - get_top_hitbox_side();

    bool touching_left = left_diff > 0 && left_diff <= get_hitbox_width();
    bool touching_right = right_diff > 0 && right_diff <= other->get_hitbox_width();
    bool touching_top = top_diff > 0 && top_diff <= get_hitbox_height();
    bool touching_bottom = bottom_diff > 0 && bottom_diff <= other->get_hitbox_height();

    return touching_left || touching_right || touching_top || touching_bottom;
}


CollisionFace CollisionObject::is_touching(const CollisionObject* other) const {

    // this method is called when a collision is detected
    // indicates what face is touching this object

    int left_diff = get_right_hitbox_side() - other->get_left_hitbox_side();
    int right_diff = other->get_right_hitbox_side() - get_left_hitbox_side();
    int top_diff = get_bottom_hitbox_side() - other->get_top_hitbox_side();
    int bottom_diff = other->get_bottom_hitbox_side() - get_top_hitbox_side();

    bool touching_left = left_diff > 0 && left_diff <= get_hitbox_width();
    bool touching_right = right_diff > 0 && right_diff <= other->get_hitbox_width();
    bool touching_top = top_diff > 0 && top_diff <= get_hitbox_height();
    bool touching_bottom = bottom_diff > 0 && bottom_diff <= other->get_hitbox_height();

    if (touching_left && left_diff < right_diff && left_diff < top_diff &&
        left_diff < bottom_diff) {
        return CollisionFace::RIGHT;
    }
    if (touching_right && right_diff < left_diff && right_diff < top_diff &&
        right_diff < bottom_diff) {
        return CollisionFace::LEFT;
    }
    if (touching_top && top_diff < left_diff && top_diff < right_diff && top_diff < bottom_diff) {
        return CollisionFace::BOTTOM;
    }
    if (touching_bottom && bottom_diff < left_diff && bottom_diff < right_diff &&
        bottom_diff < top_diff) {
        return CollisionFace::TOP;
    }

    return CollisionFace::NO_COLLISION;
}

std::string CollisionObject::get_colision(CollisionFace face) {
    switch (face) {
        case NO_COLLISION:
            return "NONE";
        case LEFT:
            return "LEFT";
        case RIGHT:
            return "RIGHT";
        case TOP:
            return "TOP";
        case BOTTOM:
            return "BOTTOM";
        default:
            return "UNKNOWN";
    }
}
