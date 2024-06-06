#ifndef _SEND_GAME_CREATED_H
#define _SEND_GAME_CREATED_H

#include "../common_message.h"

class SendConnectedToGameMessage: public Message {
private:
    ClientHasConnectedToMatchDTO game_created;

public:
    explicit SendConnectedToGameMessage(const ClientHasConnectedToMatchDTO& game_created);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendConnectedToGameMessage() override;
};

#endif
