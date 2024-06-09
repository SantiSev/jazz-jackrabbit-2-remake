#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_

#include "../game_object.h"

#include "collision_face.h"
#include "collision_object.h"

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
class CollisionObject: public GameObject {
private:
    int hitbox_width;
    int hitbox_height;
    bool is_active = true;

protected:
    /*
     * This code determines which face of the calling
     * CollisionObject instance (i.e., *this or self)
     * is being touched by the other collision object.
     */
    CollisionFace is_touching(const CollisionObject* other) const;

    /*
     * This code is identical to the is_touching method,
     * but it returns a boolean value instead of a CollisionFace.
     */
    bool is_touching_bool(const CollisionObject* other) const;

public:
    CollisionObject(int width, int height);
    CollisionObject(int x, int y, int width, int height);

    int get_left_hitbox_side() const;
    int get_right_hitbox_side() const;
    int get_top_hitbox_side() const;
    int get_bottom_hitbox_side() const;
    bool is_active_object() const;

    int get_hitbox_width() const;
    int get_hitbox_height() const;
    void set_hitbox_width(int new_width);
    void set_hitbox_height(int new_height);
    void set_active_status(bool status);

    /*
     * In case of being nececary, if i need to detect a collision
     * and act upon it, i can override this method and implement it.
     */
    virtual void handle_colision(CollisionObject* other) = 0;

    virtual ~CollisionObject() = default;
};


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
