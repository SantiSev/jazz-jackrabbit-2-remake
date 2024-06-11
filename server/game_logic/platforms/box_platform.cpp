//
// Created by santi on 06/06/24.
//

#include "box_platform.h"

#include <iostream>

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

#define box_offest 0

BoxPlatform::BoxPlatform(int x, int y, int width, int height): StaticBody(x, y, width, height) {}

void BoxPlatform::handle_colision(CollisionObject* other) {

    CollisionFace face = this->is_touching(other);
    DynamicBody* dynamic_body = dynamic_cast<DynamicBody*>(other);


    if (dynamic_body) {
        switch (face) {
            
            case CollisionFace::TOP:  // other object is on top of me
               
                dynamic_body->position.y = get_top_hitbox_side() - dynamic_body->get_hitbox_height();
                break;

            case CollisionFace::LEFT:  // other object is on my left side

                dynamic_body->position.x = get_left_hitbox_side() - dynamic_body->get_hitbox_width() - box_offest;
                break;

            case CollisionFace::RIGHT:  // other object is on the right of this object
             
                dynamic_body->position.x = get_right_hitbox_side() + box_offest;
                break;

            case CollisionFace::BOTTOM:  // other object is below me
                dynamic_body->position.y = get_bottom_hitbox_side();
                break;
            default:
                break;
        }
    }
}
