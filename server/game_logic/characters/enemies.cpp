
#include "enemies.h"

MadHatter::MadHatter(uint16_t id, int x, int y, int w, int h,
                     const std::shared_ptr<Configuration>& config):
        Enemy(id, MAD_HATTER, x, y, w, h, config) {}

LizardGoon::LizardGoon(uint16_t id, int x, int y, int w, int h,
                       const std::shared_ptr<Configuration>& config):
        Enemy(id, LIZARD_GOON, x, y, w, h, config) {}
