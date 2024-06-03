#ifndef _RECV_LEAVE_MATCH_H
#define _RECV_LEAVE_MATCH_H

#include <cstdint>

#include "../common_message.h"

class RecvLeaveMatchMessage: public Message {
private:
    LeaveMatchDTO leave_match;

public:
    explicit RecvLeaveMatchMessage(LeaveMatchDTO& leave_match);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvLeaveMatchMessage();
};

#endif
