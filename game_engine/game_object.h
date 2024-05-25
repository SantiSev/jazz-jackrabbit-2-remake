
#ifndef GAME_ENGINE_GAME_OBJECT_H_
#define GAME_ENGINE_GAME_OBJECT_H_
#include "math/vector2D.h"

class GameObject {
protected:
    Vector2D position;  // la posicion del objeto

public:
    GameObject(): position(0, 0) {}
    GameObject(float x, float y): position(x, y) {}

    virtual void setPosition(Vector2D newPosition) { position = newPosition; }

    Vector2D getPosition() const { return position; }
};


#endif  // GAME_ENGINE_GAME_OBJECT_H_
