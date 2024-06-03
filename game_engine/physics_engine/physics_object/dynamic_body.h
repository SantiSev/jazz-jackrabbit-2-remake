//
// Created by santi on 24/05/24.
//

#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../colision_object.h"
class DynamicBody: public CollisionObject {
private:
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D old_position_reference;

protected:
    Vector2D update_position(Vector2D newPosition) override;

public:
    DynamicBody(int width, int height);
    DynamicBody(int x, int y, int width, int height);
    DynamicBody(int x, int y, int width, int height, Vector2D base_speed,
                Vector2D base_acceleration);

    // para accelerar el movimiento el deltatime debe ser
    // positivo y para desacelerar debe ser negativo

    Vector2D move_horizontal(int deltaTime);

    Vector2D move_vertical(int deltaTime);

    void update_velocity(int deltaTime);

    void set_velocity(Vector2D newVelocity);

    void set_acceleration(Vector2D newAcceleration);

    void revert_position();

    Vector2D stop_movement();

    Vector2D get_velocity() const;

    Vector2D get_acceleration() const;

    Vector2D get_update_position_reference() const;

    void handle_colision(CollisionObject& other) override;
};


#endif  // CHARACTER_BODY_H
