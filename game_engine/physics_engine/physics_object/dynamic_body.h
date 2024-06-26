#ifndef CHARACTER_BODY_H
#define CHARACTER_BODY_H

#include "../collision_object.h"

namespace engine {


class DynamicBody: public engine::CollisionObject {
public:
    Vector2D velocity = Vector2D(0, 0);

    DynamicBody(int width, int height);
    DynamicBody(int x, int y, int width, int height);
    DynamicBody(int x, int y, int width, int height, Vector2D base_speed);

    /*
     * Updates the body's position based on its velocity
     * This method should be called every frame make sure the body is updated
     */
    virtual void update_body();

    void handle_colision(engine::CollisionObject* other) override;

    virtual void print_info();

    virtual void handle_out_of_bounds() {}
};
}


#endif  // CHARACTER_BODY_H
