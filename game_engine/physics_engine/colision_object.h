//
// Created by santi on 24/05/24.
//

#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_

#include "../game_object.h"

#include "colision_face.h"

/*
 * For every ColisionObject, its fundamental to take into account
 * 1. This class is the base class for all objects that can collide
 * 2. The hitbox is a rectangle, so it has a width and a height.
 * 3. detect_colision is a virtual method that must be overriden by the child class
 * 4. every child class must create their own handle_colision method, which will be called by
 * detect_colision
 * 5. handle_collision is not a virtual method here because each child class can have different
 * signatures for that function
 */
class ColisionObject: public GameObject {
private:
    int hitbox_width;
    int hitbox_height;

protected:
    /*
     * This code determines which face of the calling
     * CollisionObject instance (i.e., *this or self)
     * is being touched by the other collision object.
     */
    CollisionFace is_touching(const ColisionObject& other) const;

    /*
     * This code is identical to the is_touching method,
     * but it returns a boolean value instead of a CollisionFace.
     */
    bool is_touching_bool(const ColisionObject& other) const;

public:
    ColisionObject(int width, int height);
    ColisionObject(int x, int y, int width, int height);

    int get_left_hitbox_side() const;
    int get_right_hitbox_side() const;
    int get_top_hitbox_side() const;
    int get_bottom_hitbox_side() const;

    int get_hitbox_width() const;
    int get_hitbox_height() const;
    void set_hitbox_width(int new_width);
    void set_hitbox_height(int new_height);

    /*
     * In case of being nececary, if i need to detect a collision
     * and act upon it, i can override this method and implement it.
     */
    virtual void detect_colision(ColisionObject& other);
};


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
