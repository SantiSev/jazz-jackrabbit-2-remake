#ifndef TP_FINAL_CHARACTER_ENUM_H
#define TP_FINAL_CHARACTER_ENUM_H

#include <cstdint>
#include <string>

typedef enum: uint8_t {
    JAZZ_CHARACTER = 0x00,
    SPAZ_CHARACTER = 0x01,
    LORI_CHAARCTER = 0x02
} character_t;


inline std::string character_to_string(character_t character) {
    switch (character) {
        case JAZZ_CHARACTER:
            return "Jazz";
        case SPAZ_CHARACTER:
            return "Spaz";
        case LORI_CHAARCTER:
            return "Lori";
        default:
            return "Invalid character";
    }
}

#endif
