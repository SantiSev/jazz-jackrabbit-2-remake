#ifndef TP_FINAL_ENEMY_H
#define TP_FINAL_ENEMY_H


#include "character.h"

class Enemy: public CharacterBody {
private:
    uint8_t attack_damage = 0;
    int attack_cooldown = 0;
    bool is_attacking = false;
    int x_speed = 0;
    Vector2D spawn_position;

public:
    Enemy(size_t id, const character_t& character, int attack_damage, int health,
          int revive_cooldown, int x, int y, int w, int h, int speed);

    //------- Overrided Methods --------

    void update_db() override;
    void handle_colision(CollisionObject* other) override;

    //------- Movement Methods --------

    void attack(CharacterBody* player);
    void move_left() override;
    void move_right() override;

    //------- Revive Methods --------

    void revive();

    //------- Game Methods --------

    void update_status();

    void patrol(int match_time);
};


#endif
