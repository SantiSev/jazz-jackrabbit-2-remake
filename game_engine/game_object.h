
#ifndef GAME_ENGINE_GAME_OBJECT_H_
#define GAME_ENGINE_GAME_OBJECT_H_
#include "math/vector2D.h"

class GameObject {
public:
    Vector2D position;

    GameObject(): position(0, 0) {}
    GameObject(int x, int y): position(x, y) {}

    virtual ~GameObject() = default;
};

#endif  // GAME_ENGINE_GAME_OBJECT_H_
