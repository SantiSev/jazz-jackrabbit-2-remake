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

typedef uint16_t id_player_t;
typedef uint16_t id_match_t;

typedef enum: uint8_t { INFINITY_AMMO } cheat_command_t;

typedef enum: uint8_t {
    MOVE_LEFT = 0x00,
    MOVE_RIGHT = 0x01,
    MOVE_LEFT_FAST = 0x02,
    MOVE_RIGHT_FAST = 0x03,
    JUMP = 0x04,
    ESPECIAL_ATTACK = 0x05
} command_t;

typedef enum: uint8_t {
    JAZZ_CHARACTER = 0x00,
    SPAZ_CHARACTER = 0x01,
    LORI_CHAARCTER = 0x02
} character_t;

struct CheatCommandDTO {
    id_player_t id_player;
    cheat_command_t command;
} __attribute__((packed));

struct CommandDTO {
    id_player_t id_player;
    command_t command;
} __attribute__((packed));

struct LeaveMatchDTO {
    id_player_t id_player;
} __attribute__((packed));

struct FinishMatchDTO {
} __attribute__((packed));

struct GameStateDTO {
} __attribute__((packed));

struct CreateGameDTO {
    id_player_t id_player;
    char match_name[50];
} __attribute__((packed));

struct JoinMatchDTO {
    id_player_t id_player;
    id_match_t id_match;
    character_t player_character;
} __attribute__((packed));

struct ActiveGamesDTO {
    char name[50];
    uint8_t players;
} __attribute__((packed));

struct GameCreatedDTO {
} __attribute__((packed));

#endif
