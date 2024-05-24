//
// Created by santi on 24/05/24.
//

#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_
#include "../game_object.h"

#include "colision_box.h"

// TODO AVERIGUAR COMO CHEQUEAR COLISIONES DE OBJETOS
class ColisionObject: public GameObject {
private:
    ColisionBox colisionBox;

public:
    ColisionObject::ColisionObject(float width, float height): colisionBox(width, height) {}

    ColisionObject::ColisionObject(float x, float y, float width, float height):
            GameObject(x, y), colisionBox(x, y, width, height) {}

    float getWidth() const { return colisionBox.get_width(); }
    float getHeight() const { return colisionBox.get_height(); }

    void setPosition(Vector2D newPosition) override {
        position = newPosition;
        colisionBox.update_position(newPosition);
    };


    // Check if an object is colliding with another
    bool is_in_area(ColisionObject other) const {
        return colisionBox.is_touching(other.colisionBox);
    }

    virtual void handle_colision(ColisionObject other) const;
};


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
        // Copyriht 2024  S.E.V
