#ifndef _INVALID_MESSAGE_H
#define _INVALID_MESSAGE_H

#include "./common_message.h"

class InvalidMessage: public Message {
public:
    InvalidMessage();
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~InvalidMessage();
};

#endif