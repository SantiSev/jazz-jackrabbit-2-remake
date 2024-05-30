#ifndef _COMMON_DTO_H
#define _COMMON_DTO_H

#include <cstdint>
#include <string>

typedef enum { INFINTY_AMMO } cheat_command_t;

typedef enum {
    MOVE_LEFT,
    MOVE_RIGHT,
} command_t;

typedef enum { RABBIT_CHARACTER } character_t;

struct BaseDTO {
    // cppcheck-suppress unusedStructMember
    uint16_t header;
};

namespace DTO {
struct CloseConnecton: public BaseDTO {};
struct CheatCommand: public BaseDTO {
    cheat_command_t command;
};
struct Command: public BaseDTO {
    command_t command;
};
struct LeaveMatch: public BaseDTO {
    // cppcheck-suppress unusedStructMember
    uint16_t id_player;
};
struct FinishMatch: public BaseDTO {};
struct GameState: public BaseDTO {};
struct CreateGame: public BaseDTO {
    // cppcheck-suppress unusedStructMember
    uint16_t id_player;
    std::string match_name;
};
struct JoinMatch: public BaseDTO {
    // cppcheck-suppress unusedStructMember
    uint16_t id_player;
    // cppcheck-suppress unusedStructMember
    uint16_t id_match;
    character_t player_character;
};
struct ActiveGames: public BaseDTO {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t players;
};
struct GameCreated: public BaseDTO {};
}  // namespace DTO

#endif
