#ifndef TP_FINAL_MAP_ENUM_H
#define TP_FINAL_MAP_ENUM_H

#include <map>
#include <string>

typedef enum: uint8_t {
    NO_MAP = 0x00,
    MAP_1 = 0x01,
    MAP_2 = 0x02,
    MAP_3 = 0x03,
} map_list_t;

const std::map<map_list_t, std::string> map_list_to_string = {
        {MAP_1, "assets/maps/map_1"},
        {MAP_2, "assets/maps/map_2"},
        {MAP_3, "assets/maps/map_3"},
};

#endif
