#ifndef TP_FINAL_GAME_BULLETS_H
#define TP_FINAL_GAME_BULLETS_H

#include <cstdint>

class GameBullets {

private:
    int position_x;
    int position_y;
    uint8_t type;

public:
    GameBullets(int position_x, int position_y, uint8_t type);
};


#endif
