#ifndef _RECV_COMMAND_H
#define _RECV_COMMAND_H

#include "../common_message.h"

#define RECV_COMMAND 0x0101

class RecvCommandMessage: public Message {
private:
    CommandDTO command;

public:
    explicit RecvCommandMessage(const CommandDTO& command);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvCommandMessage();
};

#endif
