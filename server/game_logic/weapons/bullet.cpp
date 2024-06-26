
#include "bullet.h"

#include "../characters/player.h"


Bullet::Bullet(const uint64_t& id, const uint8_t type, Player& player_owner,
               const int& bullet_damage, const int& bullet_speed, const int& enemy_points,
               const int& player_points):
        engine::DynamicBody(player_owner.position.x, player_owner.position.y, BULLET_WIDTH, BULLET_HEIGHT,
                    Vector2D(bullet_speed * player_owner.get_direction(), 0)),
        id(id),
        type(type),
        player_owner(player_owner),
        bullet_damage(bullet_damage),
        life_span(BULLET_LIFE_SPAN),
        enemy_points(enemy_points),
        player_points(player_points) {

    position.y = player_owner.get_top_hitbox_side() + player_owner.get_shooting_height();

    if (player_owner.is_facing_right()) {
        position.x = player_owner.get_right_hitbox_side() + OFFSET_BULLET_X;
        direction = GOING_RIGHT;
    } else {
        position.x = player_owner.get_left_hitbox_side() - OFFSET_BULLET_X;
        direction = GOING_LEFT;
    }
}

uint64_t Bullet::get_id() const { return id; }

uint8_t Bullet::get_direction() const { return direction; }

uint8_t Bullet::get_type() const { return type; }

void Bullet::update_body() {

    if (is_active_object()) {

        life_span--;
        if (life_span == 0) {
            set_active_status(false);
            return;
        }
        position += velocity;
    }
}

void Bullet::handle_colision(engine::CollisionObject* other) {

    if (is_active_object() && is_touching_bool(other)) {

        set_active_status(false);

        CharacterBody* character = dynamic_cast<CharacterBody*>(other);
        Collectable* collectable = dynamic_cast<Collectable*>(other);

        if (character || collectable) {

            if (collectable ||
                character->get_id() ==
                        player_owner.get_id()) {  // avoid shooting myself or collectables
                set_active_status(true);
                return;
            }

            character->take_damage(bullet_damage);
            int knockback_dir = direction == GOING_RIGHT ? 1 : -1;
            character->knockback(knockback_dir * 10);
            if (character->is_dead()) {
                if (character->get_id() < 100) {
                    player_owner.add_points(enemy_points);
                } else {
                    player_owner.add_points(player_points);
                }
            }
        }
    }
}

void Bullet::print_info() {
    std::cout << "bullet id: " << (int)id << std::endl;
    std::cout << "bullet type: " << (int)type << std::endl;
    std::cout << "bullet direction: " << (int)direction << std::endl;
    std::cout << "bullet pos: " << (int)position.x << "," << (int)position.y << std::endl;
    std::cout << "+++++++++++++++++++++++++++++++++++++++++++" << std::endl;
}

void Bullet::handle_out_of_bounds() {
    if (is_active_object()) {
        set_active_status(false);
    }
}
