#include <string>

#include "player.h"

class Jazz: public Player {
public:
    Jazz(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};

class Spaz: public Player {
public:
    Spaz(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};

class Lori: public Player {
public:
    Lori(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager);
};
