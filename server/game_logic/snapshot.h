#ifndef TP_FINAL_SNAPSHOT_H
#define TP_FINAL_SNAPSHOT_H

#include <vector>

#include "../server_enemies.h"
#include "../server_player.h"

class Snapshot {
private:
    std::vector<Player>& players;
    std::vector<Enemies>& enemies;

public:
    Snapshot(std::vector<Player>& players, std::vector<Enemies>& enemies);
    const std::vector<Player>& get_players() const;
    const std::vector<Enemies>& get_enemies() const;

    void set_players(const std::vector<Player>& new_players);

    void set_enemies(const std::vector<Enemies>& new_enemies);
};


#endif
