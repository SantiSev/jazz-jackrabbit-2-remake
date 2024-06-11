
#ifndef ENEMIES_H
#define ENEMIES_H

#include "enemy.h"

class MadHatter: public Enemy {
public:
    MadHatter(uint16_t id, int x, int y);
};

class LizardGoon: public Enemy {
public:
    LizardGoon(uint16_t id, int x, int y);
};

#endif  // ENEMIES_H
