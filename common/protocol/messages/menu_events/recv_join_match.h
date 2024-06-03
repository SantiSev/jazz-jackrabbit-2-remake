#ifndef _RECV_JOIN_MATCH_H
#define _RECV_JOIN_MATCH_H

#include <cstdint>

#include "../common_message.h"

class RecvJoinMatchMessage: public Message {
private:
    JoinMatchDTO join_match;

public:
    explicit RecvJoinMatchMessage(JoinMatchDTO& join_match);
    void run() override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvJoinMatchMessage();
};

#endif
