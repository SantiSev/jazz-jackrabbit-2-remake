
#ifndef STATIC_BODY_H
#define STATIC_BODY_H
#include "../collision_object.h"


class StaticBody: public CollisionObject {

public:
    void handle_colision(CollisionObject* other) override;
    StaticBody(int width, int height);
    StaticBody(int x, int y, int width, int height);
};


#endif  // STATIC_BODY_H
