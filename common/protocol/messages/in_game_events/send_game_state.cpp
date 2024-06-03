#include "./send_game_state.h"

SendGameStateMessage::SendGameStateMessage(GameStateDTO& game_state):
        Message(SEND_GAME_STATE), game_state(game_state) {}

void SendGameStateMessage::run() {}

void SendGameStateMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_state(header, game_state);
}

SendGameStateMessage::~SendGameStateMessage() {}
