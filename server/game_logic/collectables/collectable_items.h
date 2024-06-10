
// create the CollectableItem class header

#ifndef COLLECTABLE_ITEM_H
#define COLLECTABLE_ITEM_H

#include "ammo.h"
#include "treasure.h"

#define AMMO_WIDTH 15
#define AMMO_HEIGHT 15

#define TREASURE_WIDTH 10
#define TREASURE_HEIGHT 10

class AmmoGunOne: public Ammo {
public:
    AmmoGunOne(int x, int y): Ammo(1, 10, x, y, AMMO_WIDTH, AMMO_HEIGHT, 10) {}
};

class AmmoGunTwo: public Ammo {
public:
    AmmoGunTwo(int x, int y): Ammo(2, 10, x, y, AMMO_WIDTH, AMMO_HEIGHT, 20) {}
};

class AmmoGunThree: public Ammo {
public:
    AmmoGunThree(int x, int y): Ammo(3, 10, x, y, AMMO_WIDTH, AMMO_HEIGHT, 30) {}
};

class Coin: public Treasure {
public:
    Coin(int x, int y): Treasure(5, x, y, TREASURE_WIDTH, TREASURE_HEIGHT, 10) {}
};

class Gem: public Treasure {
public:
    Gem(int x, int y): Treasure(10, x, y, TREASURE_WIDTH, TREASURE_HEIGHT, 10) {}
};

#endif  // COLLECTABLE_ITEM_H
