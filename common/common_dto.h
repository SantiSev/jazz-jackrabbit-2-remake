#ifndef TP_FINAL_COMMON_DTO_H
#define TP_FINAL_COMMON_DTO_H

#include <string>
#include <vector>

#include "../server/game_logic/characters/enemies.h"
#include "../server/game_logic/characters/player.h"

struct SnapshotDTO {
    std::vector<Player> players;
    std::vector<Enemies> enemies;
    // cppcheck-suppress unusedStructMember
    int minutes;
    // cppcheck-suppress unusedStructMember
    int seconds;
};

struct matchesDTO {
    std::string match_name;
    // cppcheck-suppress unusedStructMember
    size_t match_id;
    // cppcheck-suppress unusedStructMember
    int minutes;
    // cppcheck-suppress unusedStructMember
    int seconds;
    // cppcheck-suppress unusedStructMember
    size_t num_actual_players;
    // cppcheck-suppress unusedStructMember
    size_t max_players;
};
// todo sacar el suppress
#endif
