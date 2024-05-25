//
// Created by santi on 24/05/24.
//

#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_
#include "../../game_object.h"

#include "colision_box.h"

// TODO AVERIGUAR COMO CHEQUEAR COLISIONES DE OBJETOS
class ColisionObject: public GameObject {
private:
    ColisionBox colisionBox;

public:
    ColisionObject(float width, float height);

    ColisionObject(float x, float y, float width, float height);

    float getWidth();
    float getHeight();

    // Set the position of the object
    void setPosition(Vector2D newPosition) override;

    // Check if an object is colliding with another
    bool is_in_area(ColisionObject other);

    virtual void handle_colision(ColisionObject other) const;
};


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
