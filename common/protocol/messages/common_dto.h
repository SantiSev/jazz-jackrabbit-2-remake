#ifndef _COMMON_DTO_H
#define _COMMON_DTO_H

#include <cstdint>
#include <string>

struct MatchDTO {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t players;
};

#endif
