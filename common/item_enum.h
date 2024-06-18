#ifndef TP_FINAL_ITEM_ENUM_H
#define TP_FINAL_ITEM_ENUM_H

#include <map>
#include <string>

#define ITEMS_FILE "assets/items/items"

typedef enum: uint8_t {
    BULLET_ONE_ITEM = 0x00,
    BULLET_TWO_ITEM = 0x01,
    BULLET_THREE_ITEM = 0x02,
    CARROT = 0x03,
    MEAT = 0x04,
    COIN = 0x05,
    HEALTH_ICON = 0x06,
} item_t;

const std::map<item_t, std::string> map_item_to_animation_name = {
        {BULLET_ONE_ITEM, "bullet_one"},
        {BULLET_TWO_ITEM, "bullet_two"},
        {BULLET_THREE_ITEM, "bullet_three"},
        {CARROT, "carrot"},
        {MEAT, "meat"},
        {COIN, "coin"},
        {HEALTH_ICON, "health_icon"},
};

#endif
