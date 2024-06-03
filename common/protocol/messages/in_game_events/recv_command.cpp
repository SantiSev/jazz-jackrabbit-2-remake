#include "./recv_command.h"

RecvCommandMessage::RecvCommandMessage(CommandDTO& command):
        Message(RECV_COMMAND), command(command) {}

void RecvCommandMessage::run() {}

void RecvCommandMessage::send_message(CommonProtocol& protocol) {
    protocol.send_command(header, command);
}

RecvCommandMessage::~RecvCommandMessage() {}
