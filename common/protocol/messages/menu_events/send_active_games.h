#ifndef SEND_ACTIVE_GAMES_H
#define SEND_ACTIVE_GAMES_H

#include <cstdint>
#include <string>
#include <vector>

#define SEND_ACTIVE_GAMES 0x0200

#include "../common_message.h"
#include "../common_dto.h"

class SendActiveGamesMessage: public Message {
private:
    uint16_t header = SEND_ACTIVE_GAMES;
    std::vector<MatchDTO> matches;

public:
    explicit SendActiveGamesMessage(const std::vector<MatchDTO>& vector1);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendActiveGamesMessage();
};

#endif
