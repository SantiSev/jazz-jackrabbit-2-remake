#include "./send_game_state.h"

SendGameStateMessage::SendGameStateMessage() = default;

void SendGameStateMessage::send_message(CommonProtocol& protocol) { protocol.send_game_state(); }

void SendGameStateMessage::run() {}

SendGameStateMessage::SendGameStateMessage(const Snapshot& snapshot) {
    match_seconds = snapshot.get_seconds();
    match_minutes = snapshot.get_minutes();
    players = snapshot.get_players();
    enemies = snapshot.get_enemies();
}

SendGameStateMessage::~SendGameStateMessage() = default;
