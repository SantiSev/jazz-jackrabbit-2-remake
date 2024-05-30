//
// Created by santi on 24/05/24.
//

#include "character_body.h"

CharacterBody::CharacterBody(int width, int height): ColisionObject(width, height) {}

CharacterBody::CharacterBody(int width, int height, Vector2D base_speed,
                             Vector2D base_acceleration):
        ColisionObject(width, height), velocity(base_speed), acceleration(base_acceleration) {}


void CharacterBody::moveHorizontal(int deltaTime) {
    Vector2D newPosition = get_position() + Vector2D(velocity.get_x() * deltaTime, 0);
    update_position(newPosition);
}

void CharacterBody::moveVertical(int deltaTime) {
    Vector2D newPosition = get_position() + Vector2D(0, velocity.get_y() * deltaTime);
    update_position(newPosition);
}

void CharacterBody::updateVelocity(int deltaTime) {
    velocity = velocity + acceleration * deltaTime;
}

void CharacterBody::setAcceleration(Vector2D newAcceleration) {
    this->acceleration = newAcceleration;
}

void CharacterBody::setVelocity(Vector2D newVelocity) { this->velocity = newVelocity; }

void CharacterBody::stop_movement() { velocity = Vector2D(0, 0); }

Vector2D CharacterBody::getVelocity() const { return velocity; }

Vector2D CharacterBody::getAcceleration() const { return acceleration; }


void CharacterBody::handle_colision(
        ColisionObject& other) const {  // other players cant overlap with other players
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
void CharacterBody::detect_colision(ColisionObject& other) {
    handle_colision(other);
    // implementar logica de que estoy en el aire con gravedad
}
