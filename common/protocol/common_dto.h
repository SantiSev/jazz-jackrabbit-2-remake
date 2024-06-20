#ifndef _COMMON_DTO_H
#define _COMMON_DTO_H

#include <cstdint>
#include <map>
#include <string>

#include <arpa/inet.h>

#include "../character_enum.h"
#include "../common_constants.h"
#include "../map_enum.h"

#define NULL_MESSAGE 0X0000
#define ACPT_CONNECTION 0x0001
#define CLOSE_CONNECTION 0x0002

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_LEAVE_MATCH 0x0103
#define SEND_FINISH_MATCH 0x0104
#define ADD_PLAYER 0x0105

#define RECV_REQUEST_ACTIVE_GAMES 0x0200
#define RECV_CREATE_GAME 0x0201
#define SEND_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203
#define SEND_GAME_JOINED 0x0204
#define RECV_ACTIVE_GAMES 0x0205

typedef uint16_t id_client_t;
typedef uint16_t id_player_t;
typedef uint16_t id_match_t;

typedef enum: uint8_t {
    MOVE_LEFT = 0x00,
    MOVE_RIGHT = 0x01,
    MOVE_LEFT_FAST = 0x02,
    MOVE_RIGHT_FAST = 0x03,
    JUMP = 0x04,
    SPECIAL_ATTACK = 0x05,
    CHANGE_WEAPON = 0x06,
    LOOK_UP = 0x07,
    DUCK_DOWN = 0x08,
    SHOOT = 0x09,
    PAUSE_GAME = 0x10,
    TAUNT = 0x11,
} command_t;


const std::map<command_t, std::string> command_to_string = {
        {MOVE_LEFT, "MOVE_LEFT"},
        {MOVE_RIGHT, "MOVE_RIGHT"},
        {MOVE_LEFT_FAST, "MOVE_LEFT_FAST"},
        {MOVE_RIGHT_FAST, "MOVE_RIGHT_FAST"},
        {JUMP, "JUMP"},
        {SPECIAL_ATTACK, "SPECIAL_ATTACK"},
        {CHANGE_WEAPON, "CHANGE_WEAPON"},
        {LOOK_UP, "LOOK_UP"},
        {DUCK_DOWN, "DUCK_DOWN"},
        {SHOOT, "SHOOT"},
        {PAUSE_GAME, "PAUSE_GAME"},
        {TAUNT, "TAUNT"},
};

typedef enum: uint8_t {
    CHEAT_MAX_AMMO = 0x00,
    CHEAT_MAX_HEALTH = 0x01,
    CHEAT_INVINCIBLE = 0x02,
    CHEAT_REVIVE = 0x03,
    CHEAT_INFINITE_AMMO = 0x04,
    CHEAT_REVIVE_ALL = 0x05,
    CHEAT_KILL_ALL = 0x06,
} cheat_command_t;

//------Messages send by client to server --------


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

struct CreateGameDTO {
    id_client_t id_client;
    character_t character_selected;
    map_list_t map_name;
    uint8_t max_players;
} __attribute__((packed));

struct JoinMatchDTO {
    id_client_t id_client;
    id_match_t id_match;
    character_t player_character;
} __attribute__((packed));

struct AddPlayerDTO {
    char name[50];
    id_client_t id_client;
    character_t player_character;
    map_list_t map_name;
} __attribute__((packed));

struct RequestActiveGamesDTO {
    id_client_t id_client;
} __attribute__((packed));


//------Messages send by server to client --------


struct FinishMatchDTO {
} __attribute__((packed));

struct WeaponDTO {
    uint8_t weapon_name;
    uint16_t ammo;
    uint8_t is_empty;
} __attribute__((packed));

struct BulletDTO {
    uint64_t id;
    uint8_t bullet_type;
    uint8_t direction;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct EnemyDTO {
    uint16_t id;
    character_t character;
    state_t state;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct PlayerDTO {
    uint16_t id;
    char name[50];
    uint16_t health;
    character_t character;
    uint16_t points;
    state_t state;
    uint16_t x_pos;
    uint16_t y_pos;
    WeaponDTO weapons[NUM_OF_WEAPONS];
} __attribute__((packed));

struct GameStateDTO {
    uint8_t num_players;
    uint8_t num_enemies;
    uint8_t num_bullets;
    PlayerDTO players[MAX_PLAYERS];
    EnemyDTO enemies[MAX_ENEMIES];
    BulletDTO bullets[25 * MAX_PLAYERS];
    uint16_t seconds;
} __attribute__((packed));

struct ClientHasConnectedToMatchDTO {
    map_list_t map;
} __attribute__((packed));

struct ActiveGamesDTO {
    map_list_t map;
    uint8_t players_ingame;
    uint8_t players_max;
} __attribute__((packed));

struct MatchInfoDTO {
    uint8_t num_games;
    ActiveGamesDTO active_games[MAX_MATCHES_TO_CREATE];
} __attribute__((packed));


//------Messages sended by both client and server --------

struct CloseConnectionDTO {
    uint16_t id_client;
} __attribute__((packed));

#endif
