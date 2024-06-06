#ifndef TP_FINAL_SNAPSHOT_H
#define TP_FINAL_SNAPSHOT_H

#include <vector>

#include "../../server/game_logic/characters/enemy.h"
#include "../../server/game_logic/characters/player.h"
#include "../../server/game_logic/characters/weapon.h"


class Snapshot {
private:
    std::vector<Player>& players;
    std::vector<Enemies>& enemies;
    int minutes = 0;
    int seconds = 0;

public:
    Snapshot(std::vector<Player>& players, std::vector<Enemies>& enemies);
    const std::vector<Player>& get_players() const;
    const std::vector<Enemies>& get_enemies() const;

    void set_players(const std::vector<Player>& new_players);
    void set_enemies(const std::vector<Enemies>& new_enemies);

    int get_minutes() const;
    int get_seconds() const;

    void set_minutes(const int& new_minutes);
    void set_seconds(const int& new_seconds);
};


#endif
