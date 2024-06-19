#include "./recv_cheat_command.h"

RecvCheatCommandMessage::RecvCheatCommandMessage(const CheatCommandDTO& cheat_command):
        Message(RECV_CHEAT_COMMAND), cheat_command(cheat_command) {}


void RecvCheatCommandMessage::run(MessageHandler& handler) {
    handler.handle_recv_cheat_command(cheat_command);
}

void RecvCheatCommandMessage::send_message(CommonProtocol& protocol) {
    protocol.send_cheat_command(header, cheat_command);
}

RecvCheatCommandMessage::~RecvCheatCommandMessage() {}
