//
// Created by santi on 24/05/24.
//

#include "character_body.h"


CharacterBody::CharacterBody(float width, float height, float base_speed, float base_acceleration):
        ColisionObject(width, height), velocity(base_speed), acceleration(base_acceleration) {}

// para accelerar el movimiento el deltatime debe ser positivo y para desacelerar debe ser negativo
void CharacterBody::updateMovementX(float deltaTime) {
    velocity = velocity + (acceleration * deltaTime);
    float newPosition = getPositionX() + (velocity * deltaTime);
    setPosition(newPosition, getPositionY());
}

void CharacterBody::updateMovementY(float deltaTime) {
    velocity = velocity + (acceleration * deltaTime);
    float newPosition = getPositionY() + (velocity * deltaTime);
    setPosition(getPositionX(), newPosition);
}

void CharacterBody::setAcceleration(float newAcceleration) { this->acceleration = newAcceleration; }
