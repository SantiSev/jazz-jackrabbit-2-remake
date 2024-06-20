#ifndef TP_FINAL_COMMON_CONSTANTS_H
#define TP_FINAL_COMMON_CONSTANTS_H

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <string>

// Game Settings
const uint8_t MAX_MATCHES_TO_CREATE = 16;
const size_t MAX_PLAYERS =
        16;  // The match doesn't start without this many players connected to the match.
const size_t MAX_ENEMIES = 12;
#define PLAYER_KILL_POINTS 15
#define ENEMY_KILL_POINTS 5

// Type of events
const uint8_t CONNECTION_EVENT = 0x00;
const uint8_t IN_GAME_EVENT = 0x01;
const uint8_t MENU_EVENT = 0x02;
const uint8_t EDITOR_EVENT = 0x03;

// Type in game event
const uint8_t CHEAT_EVENT = 0x00;
const uint8_t PLAYER_EVENT = 0x01;

// Gameloop
const size_t MAX_EVENTS_PER_LOOP = 20;
const size_t MATCH_DURATION = 10;

// Player states
typedef enum _state: uint8_t {
    STATE_IDLE_RIGHT = 0x00,
    STATE_IDLE_LEFT = 0X01,
    STATE_SHOOTING_RIGHT = 0x02,
    STATE_SHOOTING_LEFT = 0x03,
    STATE_JUMPING_RIGHT = 0x04,
    STATE_JUMPING_LEFT = 0x05,
    STATE_SPRINTING_RIGHT = 0x06,
    STATE_SPRINTING_LEFT = 0x07,
    STATE_MOVING_LEFT = 0x08,
    STATE_MOVING_RIGHT = 0x09,
    STATE_FALLING = 0X10,
    STATE_DAMAGED = 0X11,
    STATE_INTOXICATED_IDLE = 0X12,
    STATE_INTOXICATED_MOV_RIGHT = 0X13,
    STATE_INTOXICATED_MOV_LEFT = 0X14,
    STATE_SPECIAL_RIGHT = 0X15,
    STATE_SPECIAL_LEFT = 0X16,
    STATE_DEAD = 0X17
} state_t;

const std::map<uint8_t, std::string> map_states_to_animations = {
        {STATE_IDLE_RIGHT, "idle_right"},
        {STATE_IDLE_LEFT, "idle_left"},
        {STATE_SHOOTING_RIGHT, "shooting_right"},
        {STATE_SHOOTING_LEFT, "shooting_left"},
        {STATE_JUMPING_RIGHT, "jumping_right"},
        {STATE_JUMPING_LEFT, "jumping_left"},
        {STATE_SPRINTING_RIGHT, "sprinting_right"},
        {STATE_SPRINTING_LEFT, "sprinting_left"},
        {STATE_MOVING_LEFT, "moving_left"},
        {STATE_MOVING_RIGHT, "moving_right"},
        {STATE_FALLING, "falling"},
        {STATE_DAMAGED, "damaged"},
        {STATE_INTOXICATED_IDLE, "intoxicated_idle"},
        {STATE_INTOXICATED_MOV_RIGHT, "intoxicated_moving_right"},
        {STATE_INTOXICATED_MOV_LEFT, "intoxicated_moving_left"},
        {STATE_SPECIAL_RIGHT, "special_right"},
        {STATE_SPECIAL_LEFT, "special_left"},
        {STATE_DEAD, "dead"}};

// Weapons
#define DEFAULT_WEAPON 0
#define FIRST_WEAPON 1
#define SECOND_WEAPON 2
#define THIRD_WEAPON 3
#define NUM_OF_WEAPONS 4

// Bullet config
#define BULLET_WIDTH 10
#define BULLET_HEIGHT 10
#define BULLET_SPEED 20

//


#endif
