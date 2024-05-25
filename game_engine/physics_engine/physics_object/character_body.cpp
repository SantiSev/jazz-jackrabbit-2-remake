//
// Created by santi on 24/05/24.
//

#include "character_body.h"


CharacterBody::CharacterBody(float width, float height, float base_speed, float base_acceleration):
        ColisionObject(width, height), velocity(base_speed), acceleration(base_acceleration) {}


void CharacterBody::moveHorizontal(float deltaTime) {
    Vector2D newPosition = getPosition() + Vector2D(velocity.get_x() * deltaTime, 0);
    setPosition(newPosition);
}

void CharacterBody::moveVertical(float deltaTime) {
    Vector2D newPosition = getPosition() + Vector2D(0, velocity.get_y() * deltaTime);
    setPosition(newPosition);
}

void CharacterBody::updateVelocity(float deltaTime) {
    velocity = velocity + acceleration * deltaTime;
}

// TODO no estoy seguro si esto funca, habria que hacer pruebas y ver si se puede mejorar
void CharacterBody::handle_colision(ColisionObject& other) {
    if (is_in_area(other)) {
        velocity = Vector2D(0, 0);
    }
}


void CharacterBody::setAcceleration(Vector2D newAcceleration) {
    this->acceleration = newAcceleration;
}
