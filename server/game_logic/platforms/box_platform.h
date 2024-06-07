//
// Created by santi on 06/06/24.
//

#ifndef BOX_PLATFORM_H
#define BOX_PLATFORM_H

#include "../../../game_engine/physics_engine/physics_object/static_body.h"


class BoxPLatoform: public StaticBody {

public:
    BoxPLatoform(int x, int y, int width, int height);
    void handle_colision(CollisionObject* other) override;
};


#endif  // BOX_PLATFORM_H
