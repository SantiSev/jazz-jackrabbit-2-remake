#include "./recv_create_game.h"

RecvCreateGameMessage::RecvCreateGameMessage(const CreateGameDTO& create_game):
        Message(RECV_CREATE_GAME), create_game(create_game) {}

void RecvCreateGameMessage::run(MessageHandler& handler) {
    handler.handle_recv_create_game(create_game);
}

void RecvCreateGameMessage::send_message(CommonProtocol& protocol) {
    protocol.send_create_game(header, create_game);
}

RecvCreateGameMessage::~RecvCreateGameMessage() {}
