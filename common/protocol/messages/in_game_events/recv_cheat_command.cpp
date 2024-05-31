#include "./recv_cheat_command.h"

RecvCheatCommandMessage::RecvCheatCommandMessage(uint16_t id_player, uint8_t id_cheat_command) {
    this->id_player = id_player;
    this->id_cheat_command = id_cheat_command;
}

void RecvCheatCommandMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

void RecvCheatCommandMessage::run() {}

RecvCheatCommandMessage::~RecvCheatCommandMessage() {}
