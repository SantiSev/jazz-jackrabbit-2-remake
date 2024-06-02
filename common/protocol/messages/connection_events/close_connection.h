#ifndef _CLOSING_CONNECTION_H
#define _CLOSING_CONNECTION_H
#include <cstdint>

#include "../common_message.h"

#define CLOSE_CONNECTION 0x0000

class CloseConnectionMessage: public Message {
private:
    const uint16_t header = CLOSE_CONNECTION;

public:
    CloseConnectionMessage();
    void run() override;
    void run(ClientProtocol& client_protocol) override;
    void send_message(CommonProtocol& protocol) override;
    ~CloseConnectionMessage() override;
};

#endif
