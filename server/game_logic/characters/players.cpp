#include "players.h"

Jazz::Jazz(uint16_t id, const std::string& name, int x, int y, int w, int h,
           CollisionManager& collision_manager):
        Player(id, name, JAZZ_CHARACTER, x, y, w, h, collision_manager) {}

Spaz::Spaz(uint16_t id, const std::string& name, int x, int y, int w, int h,
           CollisionManager& collision_manager):
        Player(id, name, SPAZ_CHARACTER, x, y, w, h, collision_manager) {}

Lori::Lori(uint16_t id, const std::string& name, int x, int y, int w, int h,
           CollisionManager& collision_manager):
        Player(id, name, LORI_CHARACTER, x, y, w, h, collision_manager) {}
