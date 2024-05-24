#include "./server_message.h"

#include <iostream>

Message::Message() {}
CloseConnectionMessage::CloseConnectionMessage() {}
RecvCommandMessage::RecvCommandMessage() {}
RecvCheatCommandMessage::RecvCheatCommandMessage() {}
RecvUnjoinMatchMessage::RecvUnjoinMatchMessage() {}
RecvCreateGameMessage::RecvCreateGameMessage() {}
RecvJoinMatchMessage::RecvJoinMatchMessage() {}
InvalidMessage::InvalidMessage() {}

void CloseConnectionMessage::run() { std::cout << "CLOSE_CONNECTION" << std::endl; }
void RecvCommandMessage::run() { std::cout << "RECV_COMMAND" << std::endl; }
void RecvCheatCommandMessage::run() { std::cout << "RECV_CHEAT_COMMAND" << std::endl; }
void RecvUnjoinMatchMessage::run() { std::cout << "RECV_UNJOIN_MATCH" << std::endl; }
void RecvCreateGameMessage::run() { std::cout << "RECV_CREATE_GAME" << std::endl; }
void RecvJoinMatchMessage::run() { std::cout << "RECV_JOIN_MATCH" << std::endl; }
void InvalidMessage::run() { std::cout << "INVALID_MESSAGE" << std::endl; }

Message::~Message() {}
CloseConnectionMessage::~CloseConnectionMessage() {}
RecvCommandMessage::~RecvCommandMessage() {}
RecvCheatCommandMessage::~RecvCheatCommandMessage() {}
RecvUnjoinMatchMessage::~RecvUnjoinMatchMessage() {}
RecvCreateGameMessage::~RecvCreateGameMessage() {}
RecvJoinMatchMessage::~RecvJoinMatchMessage() {}
InvalidMessage::~InvalidMessage() {}
