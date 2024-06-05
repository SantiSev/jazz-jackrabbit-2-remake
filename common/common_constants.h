#ifndef TP_FINAL_COMMON_CONSTANTS_H
#define TP_FINAL_COMMON_CONSTANTS_H

#include <cstdint>

// Game Settings
const uint8_t MAX_MATCHES_TO_CREATE = 16;
const size_t REQUIRED_PLAYERS_TO_START =
        1;  // The match doesn't start without this many players connected to the match.

// Type of events
const uint8_t CONNECTION_EVENT = 0x00;
const uint8_t IN_GAME_EVENT = 0x01;
const uint8_t MENU_EVENT = 0x02;
const uint8_t EDITOR_EVENT = 0x03;

// Type in game event
const uint8_t CHEAT_EVENT = 0x00;
const uint8_t PLAYER_EVENT = 0x01;

// Player events
// const uint8_t MOVE_LEFT = 0x01;
// const uint8_t MOVE_RIGHT = 0x02;
// const uint8_t LOOK_UP = 0x03;
// const uint8_t DUCK_DOWN = 0x04;
// const uint8_t JUMP = 0x05;
// const uint8_t SHOOT = 0x06;
// const uint8_t SPECIAL_ATTACK = 0x07;
// const uint8_t PICK_UP_ITEM = 0x08;
// const uint8_t PAUSE_GAME = 0x09;
// const uint8_t TAUNT = 0x10;

// Gameloop
const size_t MAX_EVENTS_PER_LOOP = 4;
const size_t STARTING_MATCH_TIME = 5;

// Player states
#define STATE_IDLE_RIGHT 0x00
#define STATE_IDLE_LEFT 0X01
#define STATE_SHOOTING_RIGHT 0x03
#define STATE_SHOOTING_LEFT 0x04
#define STATE_JUMPING 0x05
#define STATE_SPRINTING_RIGHT 0x06
#define STATE_SPRINTING_LEFT 0x08
#define STATE_MOVING_LEFT 0x08
#define STATE_MOVING_RIGHT 0x09
#define STATE_AIMING_UP 0x010
#define STATE_SHOOTING_UP 0x011
#define STATE_FALLING 0X12
#define STATE_DAMAGED 0X13
#define STATE_INTOXICATED 0X14
#define STATE_DEAD 0X15
#define STATE_ESPECIAL_ATTACKING 0X16
#define STATE_CROUNCHING 0X17
#define STATE_TAUNTING 0X18

// Weapons
#define DEFAULT_WEAPON 0
#define FIRST_WEAPON 1
#define SECOND_WEAPON 2
#define THIRD_WEAPON 3
#define NUM_OF_WEAPONS 4

#endif
