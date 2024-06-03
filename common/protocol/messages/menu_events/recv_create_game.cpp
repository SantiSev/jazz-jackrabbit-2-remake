#include "./recv_create_game.h"

#include <iostream>

RecvCreateGameMessage::RecvCreateGameMessage(CreateGameDTO& create_game):
        Message(RECV_CREATE_GAME), create_game(create_game) {}

void RecvCreateGameMessage::run() {}

void RecvCreateGameMessage::send_message(CommonProtocol& protocol) {
    protocol.send_create_game(header, create_game);
}

RecvCreateGameMessage::~RecvCreateGameMessage() {}
