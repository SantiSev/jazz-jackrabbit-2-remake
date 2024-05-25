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
    ColisionBox(float width, float height):
            width(width),
            height(height),
            tl_corner(0, 0),
            tr_corner(width, 0),
            bl_corner(0, height),
            br_corner(width, height) {}

    ColisionBox(float x, float y, float width, float height):
            width(width),
            height(height),
            tl_corner(x, y),
            tr_corner(width + x, y),
            bl_corner(x, height + y),
            br_corner(x + width, y + height) {}

    [[nodiscard]] Vector2D get_tl_corner() const { return tl_corner; }
    [[nodiscard]] Vector2D get_tr_corner() const { return tl_corner; }
    [[nodiscard]] Vector2D get_bl_corner() const { return bl_corner; }
    [[nodiscard]] Vector2D get_br_corner() const { return br_corner; }
    [[nodiscard]] float get_width() const { return width; }
    [[nodiscard]] float get_height() const { return height; }

    void update_position(Vector2D new_position) {
        tl_corner.set_x(new_position.get_x());
        tl_corner.set_y(new_position.get_y());
        tr_corner.set_x(new_position.get_x() + width);
        tr_corner.set_y(new_position.get_y());
        bl_corner.set_x(new_position.get_x());
        bl_corner.set_y(new_position.get_y() + height);
        br_corner.set_x(new_position.get_x() + width);
        br_corner.set_y(new_position.get_y() + height);
    }

    // create a functions that checks if this box is touching another box that i recive by parameter
    bool is_touching(const ColisionBox& other) const {
        return (tl_corner.get_x() < other.br_corner.get_x() &&
                tl_corner.get_y() < other.br_corner.get_y() &&
                tr_corner.get_x() > other.bl_corner.get_x() &&
                bl_corner.get_y() > other.tr_corner.get_y());
    }
};


#endif  // COLISION_BOX_H
