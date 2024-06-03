#include "./recv_join_match.h"

RecvJoinMatchMessage::RecvJoinMatchMessage(JoinMatchDTO& join_match):
        Message(RECV_JOIN_MATCH), join_match(join_match) {}

void RecvJoinMatchMessage::run() {}

void RecvJoinMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_join_match(header, join_match);
}

RecvJoinMatchMessage::~RecvJoinMatchMessage() {}
