#include "./recv_leave_match.h"

RecvLeaveMatchMessage::RecvLeaveMatchMessage(LeaveMatchDTO& leave_match):
        Message(RECV_LEAVE_MATCH), leave_match(leave_match) {}

void RecvLeaveMatchMessage::run() {}

void RecvLeaveMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_leave_match(header, leave_match);
}

RecvLeaveMatchMessage::~RecvLeaveMatchMessage() {}
