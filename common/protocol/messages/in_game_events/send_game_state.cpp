#include "./send_game_state.h"

SendGameStateMessage::SendGameStateMessage(const GameStateDTO& game_state):
        Message(SEND_GAME_STATE), game_state(game_state) {}

void SendGameStateMessage::run(MessageHandler& handler) {}

void SendGameStateMessage::send_message(CommonProtocol& protocol) {
    protocol.send_game_state(header, game_state);
}

SendGameStateMessage::~SendGameStateMessage() {}
