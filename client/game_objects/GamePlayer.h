#ifndef TP_FINAL_GAMEPLAYER_H
#define TP_FINAL_GAMEPLAYER_H

#include <cstdint>
#include <string>

#include "../../common/common_constants.h"


class GamePlayer {
private:
    uint16_t id;
    std::string name;
    uint16_t health = MAX_HEALTH;
    uint8_t character;
    uint16_t points = STARTING_POINTS;
    uint8_t state;
    //    WeaponDTO weapons[NUM_OF_WEAPONS];

public:
    GamePlayer(const uint16_t& id, const uint8_t& character, const uint8_t& state,
               std::string name);

    uint8_t get_id() const;

    void set_health(uint16_t i);

    void set_points(uint16_t i);

    void set_state(uint8_t points_updated);
};


#endif
