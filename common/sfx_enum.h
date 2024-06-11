#ifndef TP_FINAL_BULLET_ENUM_H
#define TP_FINAL_BULLET_ENUM_H

#include <map>
#include <string>

#define SFX_FILE "assets/sfx/sfx"

typedef enum: uint8_t {
    COMMON_BULLET = 0x00,
    BULLET_ONE = 0x01,
    BULLET_TWO = 0x02,
    BULLET_THREE = 0x03,
} bullet_type_t;

const std::map<bullet_type_t, std::string> map_bullet_to_animation_name = {
        {COMMON_BULLET, "common_bullet"},
        {BULLET_ONE, "bullet_one"},
        {BULLET_TWO, "bullet_two"},
        {BULLET_THREE, "bullet_three"},
};

#endif
