#ifndef _CLOSE_CONNECTION_H
#define _CLOSE_CONNECTION_H

#include <cstdint>

#include "../../../../client/protocol/client_protocol.h"
#include "../common_message.h"


class CloseConnectionMessage: public Message {
public:
    CloseConnectionMessage();
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~CloseConnectionMessage() override;
};

#endif
