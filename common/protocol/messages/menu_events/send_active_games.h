#ifndef _SEND_ACTIVE_GAMES_H
#define _SEND_ACTIVE_GAMES_H

#include <cstdint>
#include <string>
#include <vector>

#include "../common_message.h"

class SendActiveGamesMessage: public Message {
private:
    ActiveGamesDTO active_games;

public:
    explicit SendActiveGamesMessage(ActiveGamesDTO& active_games);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendActiveGamesMessage();
};

#endif
