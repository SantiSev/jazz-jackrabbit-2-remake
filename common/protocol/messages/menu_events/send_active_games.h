#ifndef SEND_ACTIVE_GAMES_H
#define SEND_ACTIVE_GAMES_H

#include <cstdint>
#include <string>
#include <vector>

#include "../common_message.h"

struct Match_str {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t players;
};

class SendActiveGamesMessage: public Message {
private:
    std::vector<Match_str> matches;

public:
    void run() override;
    ~SendActiveGamesMessage();

    explicit SendActiveGamesMessage(const std::vector<Match_str>& vector1);
};

#endif
