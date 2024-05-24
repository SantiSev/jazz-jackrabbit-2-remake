//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object.h"

class CharacterBody: public ColisionObject {
private:
    float velocity;
    float acceleration;

public:
    CharacterBody(float width, float height, float base_speed, float base_acceleration);

    // para accelerar el movimiento el deltatime debe ser positivo y para desacelerar debe ser
    // negativo
    void updateMovementX(float deltaTime);
    void updateMovementY(float deltaTime);
    void setAcceleration(float newAcceleration);
};


#endif  // CHARACTER_BODY_H
