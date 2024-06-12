#ifndef _RECV_LEAVE_MATCH_H
#define _RECV_LEAVE_MATCH_H

#include "../common_message.h"

#define RECV_LEAVE_MATCH 0x0103

class RecvLeaveMatchMessage: public Message {
private:
    LeaveMatchDTO leave_match;

public:
    explicit RecvLeaveMatchMessage(const LeaveMatchDTO& leave_match);
    void run(MessageHandler& handler) override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvLeaveMatchMessage() override;
};

#endif
