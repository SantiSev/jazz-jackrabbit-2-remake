//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object/colision_object.h"

class CharacterBody: public ColisionObject {
private:
    Vector2D velocity;
    Vector2D acceleration;

public:
    CharacterBody(float width, float height, float base_speed, float base_acceleration);

    // para accelerar el movimiento el deltatime debe ser positivo y para desacelerar debe ser
    // negativo
    void updateMovement(float deltaTime);

    void moveHorizontal(float deltaTime);

    void moveVertical(float deltaTime);

    void setAcceleration(Vector2D newAcceleration);
};


#endif  // CHARACTER_BODY_H
