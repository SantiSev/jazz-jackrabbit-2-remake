#ifndef _COMMON_DTO_H
#define _COMMON_DTO_H

#include <cstdint>
#include <string>

#include <arpa/inet.h>

#include "../common_constants.h"
#include "../map_enum.h"

#define CLOSE_CONNECTION 0x0000
#define ACPT_CONNECTION 0x0001

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_LEAVE_MATCH 0x0103
#define SEND_FINISH_MATCH 0x0104

#define RECV_REQUEST_ACTIVE_GAMES 0x0200
#define RECV_CREATE_GAME 0x0201
#define SEND_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203
#define SEND_GAME_JOINED 0x0204
#define RECV_ACTIVE_GAMES 0x0205

typedef uint16_t id_client_t;
typedef uint16_t id_player_t;
typedef uint16_t id_match_t;

typedef enum: uint8_t { INFINITY_AMMO } cheat_command_t;

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

typedef enum: uint8_t {
    JAZZ_CHARACTER = 0x00,
    SPAZ_CHARACTER = 0x01,
    LORI_CHAARCTER = 0x02
} character_t;


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
    map_list_t map_name;  // todo change to enum constant
    uint8_t max_players;
} __attribute__((packed));

struct JoinMatchDTO {
    id_client_t id_client;
    id_match_t id_match;
    character_t player_character;
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
    uint8_t bullet_type;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct EnemyDTO {
    uint8_t enemy_type;
    uint8_t state;
    uint16_t x_pos;
    uint16_t y_pos;
} __attribute__((packed));

struct PlayerDTO {
    uint16_t id;
    char name[50];
    uint16_t health;
    uint8_t character;
    uint16_t points;
    uint8_t state;
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
    BulletDTO bullets[50 * MAX_PLAYERS];
    uint16_t seconds;
} __attribute__((packed));

struct ClientHasConnectedToMatchDTO {
    id_player_t id_player;
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

#endif
