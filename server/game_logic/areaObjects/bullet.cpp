#include "bullet.h"

#define OFFSET_BULLET_X 3

Bullet::Bullet(Player& player_owner):
        DynamicBody(player_owner.position.x, player_owner.position.y, BULLET_WIDTH, BULLET_HEIGHT,
                    Vector2D(BULLET_SPEED * player_owner.get_direction(), DEFAULT_SPEED_Y)),
        player_owner(player_owner),
        life_span(1000) {
    if (player_owner.is_facing_right()) {
        position.x = player_owner.get_right_hitbox_side() + OFFSET_BULLET_X;
    } else {
        position.x = player_owner.get_left_hitbox_side() + OFFSET_BULLET_X;
    }
    position.y = player_owner.get_bottom_hitbox_side() - player_owner.get_hitbox_height() / 2;
}

size_t Bullet::get_life_span() const { return life_span; }

void Bullet::update_db() {
    if (is_active) {
        position += velocity;
        life_span--;
        print_info();
    }
}

void Bullet::handle_colision(CollisionObject& other) {
    if (is_touching_bool(other)) {
        is_active = false;
        other.handle_impact(*this);
    }
}

size_t Bullet::get_damage() const { return bullet_damage; }

void Bullet::get_player_points(size_t points) { player_owner.add_points(points); }

uint8_t Bullet::get_bullet_type() const { return bullet_type; }
