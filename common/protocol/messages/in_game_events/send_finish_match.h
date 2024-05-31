#ifndef _SEND_FINISH_MATCH_H
#define _SEND_FINISH_MATCH_H
#include <cstdint>

#include "../common_message.h"

#define SEND_FINISH_MATCH 0x0104

class SendFinishMatchMessage: public Message {
private:
    uint16_t header = SEND_FINISH_MATCH;

public:
    SendFinishMatchMessage();
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~SendFinishMatchMessage();
};

#endif
