#ifndef TP_FINAL_COMMON_CONSTANTS_H
#define TP_FINAL_COMMON_CONSTANTS_H

#include <cstdint>

// Game Settings
const uint8_t MAX_MATCHES_TO_CREATE = 16;
const size_t REQUIRED_PLAYERS_TO_START =
        1;  // The match doesn't start without this many players connected to the match.
const size_t MAX_ENEMIES = 6;
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
const size_t STARTING_MATCH_TIME = 60;

// Player config
#define MAX_HEALTH 100
#define MIN_HEALTH 0
#define STARTING_POINTS 0
#define REVIVE_COOLDOWN 5
#define INTOXICATON_COOLDOWN 4
#define SPECIAL_COOLDOWN 3
#define DEFAULT_SPEED_Y 10
#define DEFAULT_SPEED_X 10
#define JUMP_SPEED 25
#define GRAVITY 1
#define FRICCTION 0.1f
#define NO_SPEED 0

// Size configs
#define ENEMY_WIDTH 50
#define ENEMY_HEIGHT 50
#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

// Player states
#define STATE_IDLE_RIGHT 0x00
#define STATE_IDLE_LEFT 0X01
#define STATE_SHOOTING_RIGHT 0x02
#define STATE_SHOOTING_LEFT 0x03
#define STATE_JUMPING_RIGHT 0x04
#define STATE_JUMPING_LEFT 0x05
#define STATE_SPRINTING_RIGHT 0x06
#define STATE_SPRINTING_LEFT 0x07
#define STATE_MOVING_LEFT 0x08
#define STATE_MOVING_RIGHT 0x09
#define STATE_FALLING 0X10
#define STATE_DAMAGED 0X11
#define STATE_INTOXICATED_IDLE 0X12
#define STATE_INTOXICATED_MOV_RIGHT 0X13
#define STATE_INTOXICATED_MOV_LEFT 0X14
#define STATE_ESPECIAL_RIGHT 0X15
#define STATE_ESPECIAL_LEFT 0X16
#define STATE_DEAD 0X17


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

#endif
