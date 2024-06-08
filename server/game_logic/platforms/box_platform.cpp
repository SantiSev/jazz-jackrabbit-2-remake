//
// Created by santi on 06/06/24.
//

#include "box_platform.h"

#include "../../../game_engine/physics_engine/physics_object/dynamic_body.h"

BoxPlatform::BoxPlatform(int x, int y, int width, int height): StaticBody(x, y, width, height) {}

void BoxPlatform::handle_colision(CollisionObject* other) {

    CollisionFace face = this->is_touching(other);
    DynamicBody* dynamic_body = dynamic_cast<DynamicBody*>(other);

    if (dynamic_body) {
        switch (face) {
            case CollisionFace::TOP:  // other object is on top of me
                other->position.y = get_top_hitbox_side() - other->get_hitbox_height();
                break;
            case CollisionFace::LEFT:  // other object is on my left side
                other->position.x = get_left_hitbox_side() - other->get_hitbox_width();
                break;
            case CollisionFace::RIGHT:  // other object is on the right of this object
                other->position.x = get_right_hitbox_side();
                break;
            case CollisionFace::BOTTOM:  // other object is below me
                other->position.y = get_bottom_hitbox_side();
                break;
            default:
                // No collision detected
                break;
        }
    }
}
