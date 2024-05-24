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


void CharacterBody::setAcceleration(Vector2D newAcceleration) {
    this->acceleration = newAcceleration;
}
