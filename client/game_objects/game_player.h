#ifndef TP_FINAL_GAME_PLAYER_H
#define TP_FINAL_GAME_PLAYER_H

#include <cstdint>
#include <string>

#include "../../common/common_constants.h"


class GamePlayer {
private:
    uint16_t id;
    std::string name;
    uint16_t health = 0;
    uint8_t character;
    uint16_t points = 0;
    uint8_t state;
    //    WeaponDTO weapons[NUM_OF_WEAPONS];
    int position_x = 0;
    int position_y = 0;

public:
    GamePlayer(const uint16_t& id, const uint8_t& character, const uint8_t& state,
               std::string name);

    uint8_t get_id() const;

    void set_health(uint16_t i);

    void set_points(uint16_t i);

    void set_state(uint8_t points_updated);

    void set_position(int x, int y);
};


#endif
