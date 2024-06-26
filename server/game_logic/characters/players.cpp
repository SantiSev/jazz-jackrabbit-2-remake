#include "players.h"

Jazz::Jazz(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
           engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config):
        Player(id, name, JAZZ_CHARACTER, x, y, w, h, shooting_h, collision_manager, config) {}

Spaz::Spaz(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
           engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config):
        Player(id, name, SPAZ_CHARACTER, x, y, w, h, shooting_h, collision_manager, config) {}

Lori::Lori(uint16_t id, const std::string& name, int x, int y, int w, int h, int shooting_h,
           engine::CollisionManager& collision_manager,
           const std::shared_ptr<Configuration>& config):
        Player(id, name, LORI_CHARACTER, x, y, w, h, shooting_h, collision_manager, config) {}
