#ifndef CHARACTER_ENUM_H
#define CHARACTER_ENUM_H

#include <cstdint>
#include <map>
#include <string>

typedef enum: uint8_t {
    JAZZ_CHARACTER = 0x00,
    SPAZ_CHARACTER = 0x01,
    LORI_CHARACTER = 0x02,
    MAD_HATTER = 0x03,
    LIZARD_GOON = 0x04
} character_t;

const std::map<character_t, std::string> map_character_enum_to_string = {
        {JAZZ_CHARACTER, "assets/characters/jazz"},
        {SPAZ_CHARACTER, "assets/characters/spaz"},
        {LORI_CHARACTER, "assets/characters/lori"},
        {MAD_HATTER, "assets/characters/mad_hatter"},
        {LIZARD_GOON, "assets/characters/lizard_goon"}};

#endif  // CHARACTER_ENUM_H
