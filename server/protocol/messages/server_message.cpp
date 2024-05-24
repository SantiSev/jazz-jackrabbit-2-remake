#include "./server_message.h"

#include <iostream>

Message::Message() {}

// CONNECTION
CloseConnectionMessage::CloseConnectionMessage() {}

// IN GAME
RecvCommandMessage::RecvCommandMessage(uint16_t id_player, uint8_t id_command) {
    this->id_player = id_player;
    this->id_command = id_command;
}
RecvCheatCommandMessage::RecvCheatCommandMessage(uint16_t id_player, uint8_t id_cheat_command) {
    this->id_player = id_player;
    this->id_cheat_command = id_cheat_command;
}
RecvLeaveMatchMessage::RecvLeaveMatchMessage(uint16_t id_player) { this->id_player = id_player; }

// MENU
RecvCreateGameMessage::RecvCreateGameMessage(uint16_t id_player, const std::string& match_name) {
    this->id_player = id_player;
    this->match_name = match_name;
}
RecvJoinMatchMessage::RecvJoinMatchMessage(uint16_t id_player, uint16_t id_match,
                                           uint8_t player_character) {
    this->id_player = id_player;
    this->id_match = id_match;
    this->player_character = player_character;
}

InvalidMessage::InvalidMessage() {}

void CloseConnectionMessage::run() { std::cout << "CLOSE_CONNECTION" << std::endl; }
void RecvCommandMessage::run() {
    std::cout << "RECV_COMMAND" << std::endl;
    std::cout << int(id_player) << std::endl;
    std::cout << int(id_command) << std::endl;
}
void RecvCheatCommandMessage::run() {
    std::cout << "RECV_CHEAT_COMMAND" << std::endl;
    std::cout << int(id_player) << std::endl;
    std::cout << int(id_cheat_command) << std::endl;
}
void RecvLeaveMatchMessage::run() {
    std::cout << "RECV_UNJOIN_MATCH" << std::endl;
    std::cout << int(id_player) << std::endl;
}
void RecvCreateGameMessage::run() {
    std::cout << "RECV_CREATE_GAME" << std::endl;
    std::cout << int(id_player) << std::endl;
    std::cout << match_name << std::endl;
}
void RecvJoinMatchMessage::run() {
    std::cout << "RECV_JOIN_MATCH" << std::endl;
    std::cout << int(id_player) << std::endl;
}
void InvalidMessage::run() { std::cout << "INVALID_MESSAGE" << std::endl; }

Message::~Message() {}
CloseConnectionMessage::~CloseConnectionMessage() {}
RecvCommandMessage::~RecvCommandMessage() {}
RecvCheatCommandMessage::~RecvCheatCommandMessage() {}
RecvLeaveMatchMessage::~RecvLeaveMatchMessage() {}
RecvCreateGameMessage::~RecvCreateGameMessage() {}
RecvJoinMatchMessage::~RecvJoinMatchMessage() {}
InvalidMessage::~InvalidMessage() {}
