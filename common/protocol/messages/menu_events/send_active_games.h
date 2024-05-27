#ifndef _SEND_ACTIVE_GAMES_H
#define _SEND_ACTIVE_GAMES_H

#include <cstdint>
#include <string>
#include <vector>

#include "../common_message.h"

struct Match {
    std::string name;
    // cppcheck-suppress unusedStructMember
    uint8_t players;
};

class SendActiveGamesMessage: public Message {
private:
    std::vector<Match> matches;

public:
    explicit SendActiveGamesMessage(std::vector<Match>&& matches);
    void run() override;
    ~SendActiveGamesMessage();
};

#endif
