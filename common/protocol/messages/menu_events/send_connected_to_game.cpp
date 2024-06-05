#include "./send_connected_to_game.h"

SendConnectedToGameMessage::SendConnectedToGameMessage(
        const ClientHasConnectedToMatchDTO& game_created):
        Message(SEND_GAME_CREATED), game_created(game_created) {}


void SendConnectedToGameMessage::run(MessageHandler& handler) {
    handler.handle_connected_to_match(game_created);
}

void SendConnectedToGameMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_created(header, game_created);
}

SendConnectedToGameMessage::~SendConnectedToGameMessage() = default;
