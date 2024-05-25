//
// Created by santi on 24/05/24.
//

#ifndef COLISION_BOX_H
#define COLISION_BOX_H

#include "../math/vector2D.h"


class ColisionBox {
private:
    float width;
    float height;
    Vector2D tl_corner;
    Vector2D tr_corner;
    Vector2D bl_corner;
    Vector2D br_corner;

public:
    ColisionBox(float width, float height);
    ColisionBox(float x, float y, float width, float height);

    Vector2D get_tl_corner() const;
    Vector2D get_tr_corner() const;
    Vector2D get_bl_corner() const;
    Vector2D get_br_corner() const;
    float get_width() const;
    float get_height() const;

    void update_position(Vector2D new_position);
    bool is_touching(const ColisionBox& other) const;
};


#endif  // COLISION_BOX_H
