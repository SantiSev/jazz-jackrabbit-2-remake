
#ifndef GAME_ENGINE_GAME_OBJECT_H_
#define GAME_ENGINE_GAME_OBJECT_H_
#include "math/vector2D.h"

class GameObject {
private:
    Vector2D position;  // la posicion del objeto

public:
    explicit GameObject(float x, float y): position(x, y) {}

    virtual void updatePosition(Vector2D newPos) { position = newPos; }

    Vector2D getPosition() const { return position; }
};


#endif  // GAME_ENGINE_GAME_OBJECT_H_
        // Copyriht 2024  S.E.V
