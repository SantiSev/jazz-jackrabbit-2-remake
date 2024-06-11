#include "players.h"

Jazz::Jazz(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, JAZZ_CHARACTER, x, y, collision_manager) {}

Spaz::Spaz(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, SPAZ_CHARACTER, x, y, collision_manager) {}

Lori::Lori(uint16_t id, const std::string& name, int x, int y, CollisionManager& collision_manager):
        Player(id, name, LORI_CHAARCTER, x, y, collision_manager) {}
