
#ifndef PLAYERS_H
#define PLAYERS_H


#include <string>

#include "player.h"

class Jazz: public Player {
public:
    Jazz(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};

class Spaz: public Player {
public:
    Spaz(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};

class Lori: public Player {
public:
    Lori(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};

#endif  // PLAYERS_H
