#ifndef _SEND_ACTIVE_GAMES_H
#define _SEND_ACTIVE_GAMES_H

#include "../common_message.h"

class SendActiveGamesMessage: public Message {
private:
    ActiveGamesDTO active_games;

public:
    explicit SendActiveGamesMessage(const ActiveGamesDTO& active_games);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendActiveGamesMessage() override;
};

#endif
