#include "./recv_command.h"

RecvCommandMessage::RecvCommandMessage(uint16_t id_player, uint8_t id_command) {
    this->id_player = id_player;
    this->id_command = id_command;
}

void RecvCommandMessage::run() {}

RecvCommandMessage::~RecvCommandMessage() {}
