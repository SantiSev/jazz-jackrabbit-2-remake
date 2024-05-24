
#ifndef GAME_ENGINE_GAME_OBJECT_H_
#define GAME_ENGINE_GAME_OBJECT_H_
#include "math/vector2D.h"

class GameObject {
private:
    Vector2D position;  // la posicion del objeto

public:
    GameObject(): position(0, 0) {}
    GameObject(float x, float y): position(x, y) {}

    virtual void setPositionX(float x) { position.set_x(x); }

    virtual void setPositionY(float y) { position.set_y(y); }

    virtual void setPosition(float x, float y) {
        position.set_x(x);
        position.set_y(y);
    }

    [[nodiscard]] float getPositionX() const { return position.get_x(); }

    [[nodiscard]] float getPositionY() const { return position.get_y(); }
};


#endif  // GAME_ENGINE_GAME_OBJECT_H_
        // Copyriht 2024  S.E.V
