//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object.h"
#include "../collision_manager.h"

class CharacterBody: public ColisionObject {
private:
    Vector2D velocity;
    Vector2D acceleration;

protected:
    void handle_colision(ColisionObject& other) const;


public:
    CharacterBody(int width, int height);
    CharacterBody(int width, int height, Vector2D base_speed, Vector2D base_acceleration);

    // para accelerar el movimiento el deltatime debe ser
    // positivo y para desacelerar debe ser negativo

    void moveHorizontal(int deltaTime);

    void moveVertical(int deltaTime);

    void updateVelocity(int deltaTime);

    void setVelocity(Vector2D newVelocity);

    void setAcceleration(Vector2D newAcceleration);

    void stop_movement();

    Vector2D getVelocity() const;

    Vector2D getAcceleration() const;

    void detect_colision(ColisionObject& other) override;
};


#endif  // CHARACTER_BODY_H
