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

struct BaseDTO {
    virtual int size() = 0;
} __attribute__((packed));

struct CloseConnection: public BaseDTO {
    const uint16_t header = htons(CLOSE_CONNECTION);
    CloseConnection() {}
    int size() override { return sizeof(CloseConnection) - sizeof(BaseDTO); }
} __attribute__((packed));

struct CheatCommand: public BaseDTO {
    const uint16_t header = htons(RECV_CHEAT_COMMAND);
    cheat_command_t command;
    int size() override { return sizeof(CheatCommand) - sizeof(BaseDTO); }
} __attribute__((packed));

struct Command: public BaseDTO {
    const uint16_t header = htons(RECV_COMMAND);
    command_t command;
    explicit Command(command_t command): command(command) {}
    int size() override { return sizeof(Command) - sizeof(BaseDTO); }
} __attribute__((packed));

struct LeaveMatch: public BaseDTO {
    const uint16_t header = htons(RECV_LEAVE_MATCH);
    uint16_t id_player;
    explicit LeaveMatch(uint16_t id_player): id_player(htons(id_player)) {}
    int size() override { return sizeof(LeaveMatch) - sizeof(BaseDTO); }
} __attribute__((packed));

struct FinishMatch: public BaseDTO {
    const uint16_t header = htons(SEND_FINISH_MATCH);
    int size() override { return sizeof(FinishMatch) - sizeof(BaseDTO); }
} __attribute__((packed));

struct GameState: public BaseDTO {
    const uint16_t header = htons(SEND_GAME_STATE);
    int size() override { return sizeof(GameState) - sizeof(BaseDTO); }
} __attribute__((packed));

struct CreateGame: public BaseDTO {
    const uint16_t header = htons(RECV_CREATE_GAME);
    uint16_t id_player;
    char match_name[256];
    {}
} __attribute__((packed));

struct JoinMatch: public BaseDTO {
    const uint16_t header = htons(RECV_JOIN_MATCH);
    uint16_t id_player;
    uint16_t id_match;
    character_t player_character;
    int size() override { return sizeof(JoinMatch) - sizeof(BaseDTO); }
} __attribute__((packed));

struct ActiveGames: public BaseDTO {
    const uint16_t header = htons(SEND_ACTIVE_GAMES);
    char name[256];
    uint8_t players;
    int size() override { return sizeof(ActiveGames) - sizeof(BaseDTO); }
} __attribute__((packed));

struct GameCreated: public BaseDTO {
    const uint16_t header = htons(SEND_GAME_CREATED);
    int size() override { return sizeof(GameCreated) - sizeof(BaseDTO); }
} __attribute__((packed));

#endif
