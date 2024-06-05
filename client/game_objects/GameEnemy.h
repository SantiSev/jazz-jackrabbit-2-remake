#ifndef TP_FINAL_GAMEENEMY_H
#define TP_FINAL_GAMEENEMY_H

#include <cstdint>
#include <cstring>

#include "../../common/common_constants.h"

class GameEnemy {
private:
    size_t id;
    size_t health = MAX_HEALTH * 0.75;
    uint8_t state;
    uint8_t enemy_type;

public:
    GameEnemy(const uint8_t& enemy_type, const size_t& id, const uint8_t& state);

    void set_health(uint16_t updated_health);

    void set_state(uint8_t updated_state);
};

#endif
