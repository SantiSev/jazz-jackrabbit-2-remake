#ifndef TP_FINAL_GAME_ENEMY_H
#define TP_FINAL_GAME_ENEMY_H

#include <cstdint>
#include <cstring>

#include "../../common/common_constants.h"

class GameEnemy {
private:
    uint8_t state;
    uint8_t enemy_type;
    int position_x = 0;
    int position_y = 0;

public:
    GameEnemy(const uint8_t& enemy_type, const uint8_t& state);

    void set_health(uint16_t updated_health);

    void set_state(uint8_t updated_state);

    void set_position(int x, int y);

    uint8_t get_state() const;
};

#endif
