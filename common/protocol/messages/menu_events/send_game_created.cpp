#include "./send_game_created.h"

SendGameCreatedMessage::SendGameCreatedMessage(GameCreatedDTO& game_created):
        Message(SEND_GAME_CREATED), game_created(game_created) {}

void SendGameCreatedMessage::run() {}

void SendGameCreatedMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_created(header, game_created);
}

SendGameCreatedMessage::~SendGameCreatedMessage() {}
