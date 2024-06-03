#ifndef _COMMON_MESSAGE_H
#define _COMMON_MESSAGE_H

#include "../common_protocol.h"

class CommonProtocol;

class Message {
protected:
    const uint16_t header;

public:
    explicit Message(const uint16_t header);
    uint16_t get_header() const;
    virtual void send_message(CommonProtocol& protocol) = 0;
    virtual void run() = 0;
    ~Message();
};

#endif
