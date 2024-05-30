#include "./send_active_games.h"

void SendActiveGamesMessage::run() {}

SendActiveGamesMessage::SendActiveGamesMessage(const std::vector<MatchDTO>& vector1) {}

void SendActiveGamesMessage::send_message(CommonProtocol& protocol) {
    protocol.send_active_games(matches.size(), matches);
}

SendActiveGamesMessage::~SendActiveGamesMessage() = default;
