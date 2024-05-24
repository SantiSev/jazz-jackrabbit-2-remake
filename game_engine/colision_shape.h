//
// Created by santi on 24/05/24.
//

#ifndef GAME_ENGINE_COLISION_SHAPE_H_
#define GAME_ENGINE_COLISION_SHAPE_H_

class ColisionShape {
private:
    float width;
    float height;

public:
    explicit ColisionShape(float width, float height): width(width), height(height) {}

    virtual calculateArea() = 0;
};

#endif  // GAME_ENGINE_COLISION_SHAPE_H_
        // Copyriht 2024  S.E.V
