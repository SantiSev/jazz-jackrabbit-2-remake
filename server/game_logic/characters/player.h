#ifndef TP_FINAL_PLAYER_H
#define TP_FINAL_PLAYER_H

#include <string>

#include "../../../game_engine/physics_engine/physics_object/character_body.h"

#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0

class Player {
private:
    CharacterBody character_body;
    size_t id;
    std::string name;
    size_t health;
    size_t points;

public:
    Player(size_t id, std::string name, std::string character);

    size_t get_id() const;
    Vector2D get_position() const;
    std::string get_name();
    size_t get_health() const;
    size_t get_points() const;


    void increase_points(size_t new_points);
    void decrease_health(size_t susbstract_health);
    void increase_health(size_t add_health);
};


#endif
