
#ifndef AREA_OBJECT_H
#define AREA_OBJECT_H

#include "../../../game_engine/physics_engine/physics_object/static_body.h"

class Collectable: public StaticBody {
private:
    bool collected = false;

public:
    Collectable(int x, int y, int hitbox_width, int hitbox_height):
            StaticBody(x, y, hitbox_width, hitbox_height) {}
    bool is_collected() const;
    void has_been_collected() { collected = true; }
};


#endif  // AREA_OBJECT_H
