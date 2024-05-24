#ifndef TP_FINAL_SERVER_PLAYER_H
#define TP_FINAL_SERVER_PLAYER_H

#include <cstdio>
#include <string>

#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0

class Player {
private:
    size_t id;
    std::string name;
    size_t health;
    std::string character;
    size_t points;


public:
    Player(size_t id, std::string name, std::string character);

    size_t get_id() const;
    std::string get_name();
    size_t get_health() const;
    std::string get_character();
    size_t get_points() const;

    void set_id(size_t id);
    void set_name(std::string name);
    void set_health(size_t health);
    void set_character(std::string character);
    void set_points(size_t points);
    void increase_points(size_t new_points);
    void decrease_health(size_t susbstract_health);
    void increase_health(size_t add_health);
};


#endif
