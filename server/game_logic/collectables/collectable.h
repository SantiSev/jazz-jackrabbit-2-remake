
#ifndef AREA_OBJECT_H
#define AREA_OBJECT_H

#include "../../../game_engine/physics_engine/physics_object/static_body.h"

class Collectable: public StaticBody {
private:
    bool collected = false;
    int appearance_time = 0;  // TODO IMPLEMENTAR

public:
    Collectable(int x, int y, int hitbox_width, int hitbox_height):
            StaticBody(x, y, hitbox_width, hitbox_height) {}
    bool is_collected() const;
    void has_been_collected() {
        collected = true;
        set_active_status(false);
    }
};


#endif  // AREA_OBJECT_H
