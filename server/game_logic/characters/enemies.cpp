
#include "enemies.h"

#define OFFSET(h) ((h)*0.45)

#define MAD_HATTER_ATTACK_DAMAGE 10
#define MAD_HATTER_HEALTH 100
#define MAD_HATTER_REVIVE_COOLDOWN 120

#define MAD_HATTER_SPEED 3

#define LIZARD_GOON_ATTACK_DAMAGE 10
#define LIZARD_GOON_HEALTH 100
#define LIZARD_GOON_REVIVE_COUNTDOWN 120

#define LIZARD_GOON_SPEED 1


MadHatter::MadHatter(uint16_t id, int x, int y, int w, int h,
                     const std::shared_ptr<Configuration>& config):
        Enemy(id, MAD_HATTER, config->enemy_damage, config->enemy_health, config->enemy_spawn_cd, x,
              y, w, h - OFFSET(h), config->enemy_speed, config) {}

LizardGoon::LizardGoon(uint16_t id, int x, int y, int w, int h,
                       const std::shared_ptr<Configuration>& config):
        Enemy(id, LIZARD_GOON, config->enemy_damage, config->enemy_health, config->enemy_spawn_cd,
              x, y, w, h - OFFSET(h), config->enemy_speed, config) {}
