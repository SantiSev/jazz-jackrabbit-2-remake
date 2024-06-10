#include "players.h"

Jazz::Jazz(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, JAZZ_CHARACTER, x, y, collision_manager) {}

Spaz::Spaz(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, SPAZ_CHARACTER, x, y, collision_manager) {}

Lori::Lori(size_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, LORI_CHAARCTER, x, y, collision_manager) {}
