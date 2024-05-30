#ifndef _SEND_GAME_STATE_H
#define _SEND_GAME_STATE_H

#include <cstdint>

#include "../../common_protocol.h"
#include "../common_message.h"

#define SEND_GAME_STATE 0x0100

class SendGameStateMessage: public Message {
private:
    uint16_t header = SEND_GAME_STATE;

public:
    SendGameStateMessage();
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendGameStateMessage();
};

#endif