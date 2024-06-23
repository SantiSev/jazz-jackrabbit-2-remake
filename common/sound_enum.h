#ifndef TP_FINAL_SOUND_ENUM_H
#define TP_FINAL_SOUND_ENUM_H

#include <map>
#include <string>

#define INFINITY_LOOP -1

typedef enum: uint8_t {
    BACKGROUND = 0x00,
    SHOOT_SOUND = 0x01,
    CHARACTER_SELECT_SOUND = 0x02,
} sound_type_t;

const std::map<sound_type_t, std::string> sound_to_string = {
        {BACKGROUND, "assets/sounds/background"},
        {SHOOT_SOUND, "assets/sounds/shoot"},
        {CHARACTER_SELECT_SOUND, "assets/sounds/character_select"},
};

#endif
