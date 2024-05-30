#include "./recv_command.h"

RecvCommandMessage::RecvCommandMessage(const uint16_t& id_player, const uint8_t& id_command):
        id_player(id_player), id_command(id_command) {}

void RecvCommandMessage::run() {}

void RecvCommandMessage::send_message(CommonProtocol& protocol) {
    //   protocol.send_cheat_command();
}

RecvCommandMessage::~RecvCommandMessage() {}
