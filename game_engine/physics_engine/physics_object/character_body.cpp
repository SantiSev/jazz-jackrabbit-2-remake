//
// Created by santi on 24/05/24.
//

#include "character_body.h"

CharacterBody::CharacterBody(int width, int height): ColisionObject(width, height) {}

CharacterBody::CharacterBody(int width, int height, Vector2D base_speed,
                             Vector2D base_acceleration):
        ColisionObject(width, height), velocity(base_speed), acceleration(base_acceleration) {}


void CharacterBody::moveHorizontal(int deltaTime) {
    Vector2D newPosition = getPosition() + Vector2D(velocity.get_x() * deltaTime, 0);
    setPosition(newPosition);
}

void CharacterBody::moveVertical(int deltaTime) {
    Vector2D newPosition = getPosition() + Vector2D(0, velocity.get_y() * deltaTime);
    setPosition(newPosition);
}

void CharacterBody::updateVelocity(int deltaTime) {
    velocity = velocity + acceleration * deltaTime;
}

void CharacterBody::setAcceleration(Vector2D newAcceleration) {
    this->acceleration = newAcceleration;
}

Vector2D CharacterBody::getVelocity() const { return velocity; }

Vector2D CharacterBody::getAcceleration() const { return acceleration; }

// TODO no estoy seguro si esto funca, habria que hacer pruebas y ver si se puede mejorar
void CharacterBody::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        velocity = Vector2D(0, 0);
    }
}
