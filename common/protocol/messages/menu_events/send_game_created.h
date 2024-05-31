#ifndef _SEND_GAME_CREATED_H
#define _SEND_GAME_CREATED_H

#include <cstdint>

#define SEND_GAME_CREATED 0x0202

#include "../common_message.h"

class SendGameCreatedMessage: public Message {
private:
    uint16_t header = SEND_GAME_CREATED;

public:
    SendGameCreatedMessage();
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendGameCreatedMessage();
};

#endif
