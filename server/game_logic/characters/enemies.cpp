
#include "enemies.h"

#define MAD_HATTER_ATTACK_DAMAGE 10
#define MAD_HATTER_HEALTH 100
#define MAD_HATTER_REVIVE_COOLDOWN 120

#define MAD_HATTER_SPEED 3

#define LIZARD_GOON_ATTACK_DAMAGE 10
#define LIZARD_GOON_HEALTH 100
#define LIZARD_GOON_REVIVE_COUNTDOWN 120

#define LIZARD_GOON_SPEED 1

MadHatter::MadHatter(uint16_t id, int x, int y, int w, int h):
        Enemy(id, MAD_HATTER, MAD_HATTER_ATTACK_DAMAGE, MAD_HATTER_HEALTH,
              MAD_HATTER_REVIVE_COOLDOWN, x, y, w, h, MAD_HATTER_SPEED) {}

LizardGoon::LizardGoon(uint16_t id, int x, int y, int w, int h):
        Enemy(id, LIZARD_GOON, LIZARD_GOON_ATTACK_DAMAGE, LIZARD_GOON_HEALTH,
              LIZARD_GOON_REVIVE_COUNTDOWN, x, y, w, h, LIZARD_GOON_SPEED) {}
