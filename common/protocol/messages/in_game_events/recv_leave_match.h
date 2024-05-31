#ifndef _RECV_LEAVE_MATCH_H
#define _RECV_LEAVE_MATCH_H
#include <cstdint>

#include "../common_message.h"

#define RECV_LEAVE_MATCH 0x0103

class RecvLeaveMatchMessage: public Message {
private:
    uint16_t header = RECV_LEAVE_MATCH;
    uint16_t id_player;

public:
    explicit RecvLeaveMatchMessage(uint16_t id_player);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvLeaveMatchMessage();
};

#endif
