#include "send_game_joined.h"

SendGameJoined::SendGameJoined(const ClientHasConnectedToMatchDTO& game_joined):
        Message(SEND_GAME_JOINED), game_joined(game_joined) {}

void SendGameJoined::SendGameJoined::run(MessageHandler& handler) {
    handler.handle_joined_match(game_joined);
}

void SendGameJoined::SendGameJoined::send_message(CommonProtocol& protocol) {
    protocol.send_game_joined(header, game_joined);
}

SendGameJoined::SendGameJoined::~SendGameJoined() = default;
