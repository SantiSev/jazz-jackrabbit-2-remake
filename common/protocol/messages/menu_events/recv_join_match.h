#ifndef _RECV_JOIN_MATCH_H
#define _RECV_JOIN_MATCH_H

#include "../common_message.h"

class RecvJoinMatchMessage: public Message {
private:
    JoinMatchDTO join_match;

public:
    explicit RecvJoinMatchMessage(JoinMatchDTO& join_match);
    void run() override;
    void run(MatchesManager& matches_manager) override;
    void send_message(CommonProtocol& protocol) override;
    ~RecvJoinMatchMessage();
};

#endif
