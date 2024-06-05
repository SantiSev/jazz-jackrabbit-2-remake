#ifndef _SEND_ACTIVE_GAMES_H
#define _SEND_ACTIVE_GAMES_H

#include "../common_message.h"

class SendRequestGamesMessage: public Message {
private:
    RequestActiveGamesDTO active_games;

public:
    explicit SendRequestGamesMessage(const RequestActiveGamesDTO& active_games);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendRequestGamesMessage() override;
};

#endif
