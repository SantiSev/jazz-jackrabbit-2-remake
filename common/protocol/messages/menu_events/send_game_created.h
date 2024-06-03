#ifndef _SEND_GAME_CREATED_H
#define _SEND_GAME_CREATED_H

#include "../common_message.h"

class SendGameCreatedMessage: public Message {
private:
    GameCreatedDTO game_created;

public:
    explicit SendGameCreatedMessage(GameCreatedDTO& game_created);
    void run(ClientProtocol& client_protocol) override;
    void send_message(CommonProtocol& protocol) override;
    ~SendGameCreatedMessage() override;
};

#endif
