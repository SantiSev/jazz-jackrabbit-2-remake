#include "./recv_leave_match.h"

RecvLeaveMatchMessage::RecvLeaveMatchMessage(const LeaveMatchDTO& leave_match):
        Message(RECV_LEAVE_MATCH), leave_match(leave_match) {}


void RecvLeaveMatchMessage::run(MessageHandler& handler) {}

void RecvLeaveMatchMessage::send_message(CommonProtocol& protocol) {
    protocol.send_leave_match(header, leave_match);
}

RecvLeaveMatchMessage::~RecvLeaveMatchMessage() = default;
