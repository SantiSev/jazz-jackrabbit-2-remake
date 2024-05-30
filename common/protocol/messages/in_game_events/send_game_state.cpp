#include "./send_game_state.h"

SendGameStateMessage::SendGameStateMessage() = default;

void SendGameStateMessage::run() {}

SendGameStateMessage::SendGameStateMessage(const Snapshot& snapshot) {
    match_seconds = snapshot.get_seconds();
    match_minutes = snapshot.get_minutes();
}

SendGameStateMessage::~SendGameStateMessage() = default;
