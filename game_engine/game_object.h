
#ifndef GAME_ENGINE_GAME_OBJECT_H_
#define GAME_ENGINE_GAME_OBJECT_H_
#include "math/vector2D.h"

class GameObject {
protected:
    Vector2D position;  // la posicion del objeto

public:
    GameObject(): position(0, 0) {}
    GameObject(int x, int y): position(x, y) {}

    virtual Vector2D update_position(Vector2D newPosition) {
        position = newPosition;
        return position;
    }
    virtual Vector2D update_position(int x, int y) {
        position = Vector2D(x, y);
        return position;
    }

    Vector2D get_position() const { return position; }

    virtual ~GameObject() = default;
};


#endif  // GAME_ENGINE_GAME_OBJECT_H_
