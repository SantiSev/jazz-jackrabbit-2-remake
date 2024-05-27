//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object.h"

class CharacterBody: public ColisionObject {
private:
    Vector2D velocity;
    Vector2D acceleration;

public:
    CharacterBody(int width, int height);
    CharacterBody(int width, int height, Vector2D base_speed, Vector2D base_acceleration);

    // para accelerar el movimiento el deltatime debe ser positivo y para desacelerar debe ser
    // negativo

    void moveHorizontal(int deltaTime);

    void moveVertical(int deltaTime);

    void updateVelocity(int deltaTime);

    void handle_colision(ColisionObject& other) override;

    void setAcceleration(Vector2D newAcceleration);

    Vector2D getVelocity() const;

    Vector2D getAcceleration() const;
};


#endif  // CHARACTER_BODY_H
