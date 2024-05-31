//
// Created by santi on 24/05/24.
//

#include "dynamic_body.h"

DynamicBody::DynamicBody(int width, int height, CollisionManager& collision_manager): CollisionObject(width, height), collision_manager(collision_manager) {}

DynamicBody::DynamicBody(int x, int y, int width, int height, CollisionManager& collision_manager): CollisionObject(x, y, width, height), collision_manager(collision_manager) {}

DynamicBody::DynamicBody(int x, int y, int width, int height, Vector2D base_speed,
                             Vector2D base_acceleration, CollisionManager& collision_manager): CollisionObject(x, y, width, height),
                             velocity(base_speed), acceleration(base_acceleration),collision_manager(collision_manager) {}


Vector2D DynamicBody::move_horizontal(int deltaTime) {

    Vector2D newPosition = get_position() + Vector2D(velocity.get_x() * deltaTime, 0); //update position
    detect_colision(); // detect if there is a collision and handle it
    return update_position(newPosition); // update position internally

}

Vector2D DynamicBody::move_vertical(int deltaTime) {

    Vector2D newPosition = get_position() + Vector2D(0, velocity.get_y() * deltaTime);
    detect_colision();
    return update_position(newPosition);
}

void DynamicBody::update_velocity(int deltaTime) {
    velocity = velocity + acceleration * deltaTime;
}

void DynamicBody::set_acceleration(Vector2D newAcceleration) {
    this->acceleration = newAcceleration;
}

void DynamicBody::set_velocity(Vector2D newVelocity) { this->velocity = newVelocity; }

Vector2D DynamicBody::stop_movement() { velocity = Vector2D(0, 0); return velocity; }

Vector2D DynamicBody::get_velocity() const { return velocity; }

Vector2D DynamicBody::get_acceleration() const { return acceleration; }

Vector2D DynamicBody::update_position(Vector2D newPosition) {
    collision_manager.update__dynamic_object(this, old_position_reference);
    old_position_reference = get_position();
    return CollisionObject::update_position(newPosition);
}

void DynamicBody::handle_colision(
        CollisionObject& other) {  // other players cant overlap with other players

    CollisionFace face = is_touching(other);
    switch (face) {
        case CollisionFace::TOP:  // other object is under this object
                                  // Move other object to be just below this object
            other.update_position(other.get_position().get_x(),
                                  get_position().get_y() - other.get_hitbox_height());
            break;
        case CollisionFace::LEFT:  // other object is on the left of this object
                                   // Move other object to be just to the left of this object
            other.update_position(get_position().get_x() - other.get_hitbox_width(),
                                  other.get_position().get_y());
            break;
        case CollisionFace::RIGHT:  // other object is on the right of this object
                                    // Move other object to be just to the right of this object
            other.update_position(get_position().get_x() + get_hitbox_width(),
                                  other.get_position().get_y());
            break;
        case CollisionFace::BOTTOM:  // other object is above this object
                                     // Move other object to be just above this object
            other.update_position(other.get_position().get_x(),
                                  get_position().get_y() + get_hitbox_height());
            break;
        default:
            // No collision detected
            break;
    }
}

// When a character collides with another object, the other object should handle the collision
void DynamicBody::detect_colision() {
    for (int i = get_position().get_x(); i < get_position().get_x() + get_hitbox_width(); ++i) {
        for (int j = get_position().get_y(); j < get_position().get_y() + get_hitbox_height(); ++j) {
            std::shared_ptr<CollisionObject> other = collision_manager.get_collision_object_at(i, j);
            if (other != nullptr && other.get() != this) {
                other->handle_colision(*this);
            }
        }
    }
}
