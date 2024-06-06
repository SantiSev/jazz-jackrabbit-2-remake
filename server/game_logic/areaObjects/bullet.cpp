#include "bullet.h"

#define OFFSET_BULLET_X 3

Bullet::Bullet(std::shared_ptr<Player>& player_owner):
        DynamicBody(player_owner->position.x, player_owner->position.y, BULLET_WIDTH, BULLET_HEIGHT,
                    Vector2D(BULLET_SPEED * player_owner->get_direction(), DEFAULT_SPEED_Y)),
        player_owner(player_owner),
        life_span(10) {
    if (player_owner->is_facing_right()) {
        position.x = player_owner->get_right_hitbox_side() + OFFSET_BULLET_X;
    } else {
        position.x = player_owner->get_left_hitbox_side() + OFFSET_BULLET_X;
    }
    position.y = player_owner->get_bottom_hitbox_side() - player_owner->get_hitbox_height() / 2;
}

void Bullet::decrease_life_span() { life_span--; }

size_t Bullet::get_life_span() const { return life_span; }

void Bullet::update_db() {
    position += velocity;

    print_info();
}

void Bullet::handle_colision(CollisionObject& other) {
    if (is_touching_bool(other)) {
        impacted = true;
    }
}
