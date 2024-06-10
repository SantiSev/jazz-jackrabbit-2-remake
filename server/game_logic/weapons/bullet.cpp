
#include "bullet.h"

#include "../characters/player.h"


Bullet::Bullet(const uint64_t& id, const uint8_t type, Player& player_owner,
               const int& bullet_damage):
        DynamicBody(player_owner.position.x, player_owner.position.y, BULLET_WIDTH, BULLET_HEIGHT,
                    Vector2D(BULLET_SPEED * player_owner.get_direction(), 0)),
        id(id),
        type(type),
        player_owner(player_owner),
        bullet_damage(bullet_damage),
        life_span(BULLET_LIFE_SPAN) {

    position.y = player_owner.get_bottom_hitbox_side() - player_owner.get_hitbox_height() / 2;

    if (player_owner.is_facing_right()) {
        position.x = player_owner.get_right_hitbox_side() + OFFSET_BULLET_X;
        direction = GOING_RIGHT;
    } else {
        position.x = player_owner.get_left_hitbox_side() + OFFSET_BULLET_X;
        direction = GOING_LEFT;
    }

    SDL_Rect bullet_cube = {position.x, position.y, BULLET_WIDTH, BULLET_HEIGHT};
    SDL_Color color = {255, 165, 0, 0};
    this->color_rect = engine::ColorRect(color, bullet_cube);
}

uint64_t Bullet::get_id() const { return id; }

uint8_t Bullet::get_direction() const { return player_owner.get_direction(); }

uint8_t Bullet::get_type() const { return type; }

void Bullet::update_body() {

    if (is_active_object()) {

        update_color_rect();

        life_span--;
        if (life_span == 0) {
            set_active_status(false);
            return;
        }
        position += velocity;
    }
}

void Bullet::handle_colision(CollisionObject* other) {

    if (is_active_object() && is_touching_bool(other)) {

        set_active_status(false);

        CharacterBody* character = dynamic_cast<CharacterBody*>(other);

        if (character) {

            if (character->get_id() == player_owner.get_id()) {  // avoid shooting myself
                set_active_status(true);
                return;
            }


            character->take_damage(bullet_damage);
            player_owner.add_points(BULLET_POINTS);
            if (character->is_dead()) {
                player_owner.add_points(BULLET_BONUS_POINTS);
            }
        }
    }
}
