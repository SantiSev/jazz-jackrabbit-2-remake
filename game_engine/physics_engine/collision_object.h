#ifndef GAME_ENGINE_COLISION_OBJECT_H_
#define GAME_ENGINE_COLISION_OBJECT_H_

#include <iostream>
#include <string>

#include "../math/vector2D.h"

#include "collision_face.h"

namespace engine {
class CollisionObject {
public:
    engine::Vector2D position;

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

    /*
     * This method is used to get the name of the face that is being touched.
     * It is used for testing purposes.
     */
    std::string get_colision(CollisionFace face);

    int get_hitbox_width() const;
    int get_hitbox_height() const;
    void set_hitbox_width(int new_width);
    void set_hitbox_height(int new_height);
    void set_active_status(bool status);

    /*
     * It is required to implement this method in the derived classes.
     * This method is called when a collision is detected.
     */
    virtual void handle_colision(CollisionObject* other) = 0;

    virtual ~CollisionObject() = default;
};
}  // namespace engine


#endif  // GAME_ENGINE_COLISION_OBJECT_H_
