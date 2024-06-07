#ifndef TP_FINAL_MAP_ENUM_H
#define TP_FINAL_MAP_ENUM_H

#include <map>
#include <string>

typedef enum: uint8_t {
    MAP_1 = 0x01,
    MAP_2 = 0x02,
    MAP_3 = 0x03,
} map_list_t;

const std::map<map_list_t, std::string> map_list_to_string = {
        {MAP_1, "map_1"},
        {MAP_2, "map_2"},
        {MAP_3, "map_3"},
};

#endif
