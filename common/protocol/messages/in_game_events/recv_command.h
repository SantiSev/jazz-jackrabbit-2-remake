#ifndef _RECV_COMMAND_H
#define _RECV_COMMAND_H

#include <cstdint>

#include "../../common_dto.h"
#include "../common_message.h"

class RecvCommandMessage: public Message {
private:
    CommandDTO command;

public:
    explicit RecvCommandMessage(CommandDTO& command);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCommandMessage();
};

#endif
