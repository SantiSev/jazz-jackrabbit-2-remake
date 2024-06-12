
#ifndef AREA_OBJECT_H
#define AREA_OBJECT_H

#include "../../../game_engine/physics_engine/physics_object/static_body.h"

class Collectable: public DynamicBody {
private:
    bool collected = false;
    int respawn_cooldown = 1000;
    int respawn_counter = 0;

public:
    Collectable(int x, int y, int hitbox_width, int hitbox_height, int respawn_cooldown):
            DynamicBody(x, y, hitbox_width, hitbox_height), respawn_cooldown(respawn_cooldown) {}

    bool is_collected() const { return collected; }

    void update_body() override {
        if (collected) {
            set_active_status(false);
        }
    }

    bool try_respawn() {

        if (!collected) {
            return false;
        }

        if (respawn_cooldown == respawn_counter && !is_active_object()) {
            return true;
        } else {
            this->respawn_counter++;
            return false;
        }
    }

    virtual void respawn(Vector2D new_position) {
        position = new_position;
        set_active_status(true);
        respawn_counter = 0;
        collected = false;
    }

    void has_been_collected() {
        collected = true;
        set_active_status(false);
    }

    void print_info() override {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "| Collectable: " << position.x << " " << position.y << " |" << std::endl;
        std::cout << "| Collected: " << collected << " |" << std::endl;
        std::cout << "| Respawn Cooldown: " << respawn_cooldown << " |" << std::endl;
        std::cout << "| Respawn Counter: " << respawn_counter << " |" << std::endl;
    }
};


#endif  // AREA_OBJECT_H
