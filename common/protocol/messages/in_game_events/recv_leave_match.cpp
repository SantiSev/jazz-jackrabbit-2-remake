#include "./recv_leave_match.h"

RecvLeaveMatchMessage::RecvLeaveMatchMessage(uint16_t id_player) { this->id_player = id_player; }

void RecvLeaveMatchMessage::run() {}

void RecvLeaveMatchMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

RecvLeaveMatchMessage::~RecvLeaveMatchMessage() {}
