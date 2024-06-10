#ifndef TP_FINAL_ENEMY_H
#define TP_FINAL_ENEMY_H

#include "character.h"

// Enemy config
#define ENEMY_WIDTH 50
#define ENEMY_HEIGHT 50
#define MOVEMENT_RANGE 100

class Enemy: public CharacterBody {
private:
    uint8_t attack_damage;
    int attack_cooldown;
    bool is_attacking = false;
    int x_speed;
    int movement_range = MOVEMENT_RANGE;
    Vector2D spawn_position;

public:
    Enemy(size_t id, const character_t& character, int attack_damage, int health,
          int revive_cooldown, int x, int y, int w, int h, int speed);

    //------- Overrided Methods --------

    void update_body() override;
    void handle_colision(CollisionObject* other) override;

    //------- Movement Methods --------

    void attack(CharacterBody* player);
    void move_left() override;
    void move_right() override;

    //------- Game Methods --------

    virtual void patrol();
};


#endif
