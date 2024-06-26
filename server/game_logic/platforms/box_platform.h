

#ifndef BOX_PLATFORM_H
#define BOX_PLATFORM_H

#include "../../../game_engine/physics_engine/physics_object/static_body.h"


class BoxPlatform: public engine::StaticBody {

public:
    BoxPlatform(int x, int y, int width, int height);
    void handle_colision(engine::CollisionObject* other) override;
};


#endif  // BOX_PLATFORM_H
