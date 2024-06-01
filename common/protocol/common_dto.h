#ifndef _COMMON_DTO_H
#define _COMMON_DTO_H

#include <cstdint>
#include <string>

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_LEAVE_MATCH 0x0103
#define SEND_FINISH_MATCH 0x0104

#define SEND_ACTIVE_GAMES 0x0200
#define RECV_CREATE_GAME 0x0201
#define SEND_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203

typedef enum: uint8_t { INFINTY_AMMO } cheat_command_t;

typedef enum: uint8_t {
    MOVE_LEFT = 0x00,
    MOVE_RIGHT = 0x01,
} command_t;

typedef enum: uint8_t { RABBIT_CHARACTER } character_t;

struct CloseConnection {
    const uint16_t header = htons(CLOSE_CONNECTION);
} __attribute__((packed));

struct CheatCommand {
    const uint16_t header = htons(RECV_CHEAT_COMMAND);
    cheat_command_t command;
} __attribute__((packed));

struct Command {
    const uint16_t header = htons(RECV_COMMAND);
    command_t command;
} __attribute__((packed));

struct LeaveMatch {
    const uint16_t header = htons(RECV_LEAVE_MATCH);
    uint16_t id_player;
} __attribute__((packed));

struct FinishMatch {
    const uint16_t header = htons(SEND_FINISH_MATCH);
} __attribute__((packed));

struct GameState {
    const uint16_t header = htons(SEND_GAME_STATE);
} __attribute__((packed));

struct CreateGame {
    const uint16_t header = htons(RECV_CREATE_GAME);
    uint16_t id_player;
    char match_name[256];
} __attribute__((packed));

struct JoinMatch {
    const uint16_t header = htons(RECV_JOIN_MATCH);
    uint16_t id_player;
    uint16_t id_match;
    character_t player_character;
} __attribute__((packed));

struct ActiveGames {
    const uint16_t header = htons(SEND_ACTIVE_GAMES);
    char name[256];
    uint8_t players;
} __attribute__((packed));

struct GameCreated {
    const uint16_t header = htons(SEND_GAME_CREATED);
} __attribute__((packed));

#endif
