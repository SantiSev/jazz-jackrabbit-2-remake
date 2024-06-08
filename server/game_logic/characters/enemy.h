

#ifndef TP_FINAL_ENEMY_H
#define TP_FINAL_ENEMY_H


#include "character.h"

#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0
#define REVIVE_COOLDOWN 5

class Enemy: public CharacterBody {
private:
    uint8_t attack_damage = 0;
    int attack_cooldown = 0;
    bool is_attacking = false;
    int x_speed = 0;

public:
    Enemy(size_t id, const uint8_t& character, int attack_damage, int health, int revive_cooldown,
          int x, int y, int w, int h, int speed);

    void update_db() override;
    void handle_colision(CollisionObject* other) override;

    void attack(CharacterBody* player);

    void move_left() override;
    void move_right() override;
};


#endif
