#ifndef TP_FINAL_COMMON_CONSTANTS_H
#define TP_FINAL_COMMON_CONSTANTS_H

#include <cstdint>

// Type of events
const uint8_t CONNECTION_EVENT = 0x00;
const uint8_t IN_GAME_EVENT = 0x01;
const uint8_t MENU_EVENT = 0x02;
const uint8_t EDITOR_EVENT = 0x03;

// Type in game event
const uint8_t CHEAT_EVENT = 0x00;
const uint8_t PLAYER_EVENT = 0x01;

// Player events
const uint8_t MOVE_LEFT = 0x01;
const uint8_t MOVE_RIGHT = 0x02;
const uint8_t LOOK_UP = 0x03;
const uint8_t DUCK_DOWN = 0x04;
const uint8_t JUMP = 0x05;
const uint8_t SHOOT = 0x06;
const uint8_t SPECIAL_ATTACK = 0x07;
const uint8_t PICK_UP_ITEM = 0x08;
const uint8_t PAUSE_GAME = 0x09;
const uint8_t TAUNT = 0x10;  // Opcional

#endif
