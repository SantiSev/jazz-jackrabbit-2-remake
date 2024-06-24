
#ifndef PLAYERS_H
#define PLAYERS_H


#include <memory>
#include <string>

#include "player.h"

class Jazz: public Player {
public:
    Jazz(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
         CollisionManager& collision_manager, const std::shared_ptr<Configuration>& config);
};

class Spaz: public Player {
public:
    Spaz(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
         CollisionManager& collision_manager, const std::shared_ptr<Configuration>& config);

};

class Lori: public Player {
public:
    Lori(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
         CollisionManager& collision_manager, const std::shared_ptr<Configuration>& config);
};

#endif  // PLAYERS_H
