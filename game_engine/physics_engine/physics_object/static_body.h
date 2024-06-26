
#ifndef STATIC_BODY_H
#define STATIC_BODY_H

#include "../collision_object.h"

namespace engine {

class StaticBody: public engine::CollisionObject {

protected:
    bool top_collision = true;
    bool left_collision = true;
    bool right_collision = true;
    bool bottom_collision = true;

public:
    StaticBody(int width, int height);
    StaticBody(int x, int y, int width, int height);
    void handle_colision(engine::CollisionObject* other) override;
    void disable_collision(CollisionFace face);
};

}  // namespace engine


#endif  // STATIC_BODY_H
