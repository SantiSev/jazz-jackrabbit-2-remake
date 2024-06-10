#include "enemy.h"

class MadHatter: public Enemy {
public:
    MadHatter(size_t id, int x, int y);
};

class LizardGoon: public Enemy {
public:
    LizardGoon(size_t id, int x, int y);
};
