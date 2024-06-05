#ifndef _COMMON_MESSAGE_H
#define _COMMON_MESSAGE_H

#include <cstdint>
#include <memory>

#include "../common_protocol.h"

#include "message_handler.h"

class CommonProtocol;

class Message {
protected:
    const uint16_t header;

public:
    explicit Message(uint16_t header);
    uint16_t get_header() const;
    virtual void send_message(CommonProtocol& protocol) = 0;
    virtual void run(MessageHandler& handler) = 0;
    virtual ~Message();
};

#endif
