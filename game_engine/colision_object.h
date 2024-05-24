//
// Created by santi on 24/05/24.
//

#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_
#include "colision_shape.h"
#include "game_object.h"

class ColisionObject: public GameObject {
private:
    ColisionShape shape;

public:
    explicit ColisionObject(float x, float y, ColisionShape shape):
            GameObject(x, y), shape(shape) {}

    ColisionShape getShape() const { return shape; }
};


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
        // Copyriht 2024  S.E.V
