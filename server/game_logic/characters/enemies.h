
#ifndef ENEMIES_H
#define ENEMIES_H

#include <memory>

#include "enemy.h"

class MadHatter: public Enemy {
public:
    MadHatter(uint16_t id, int x, int y, int w, int h,
              const std::shared_ptr<Configuration>& config);
};

class LizardGoon: public Enemy {
public:
    LizardGoon(uint16_t id, int x, int y, int w, int h,
               const std::shared_ptr<Configuration>& config);
};

#endif  // ENEMIES_H
