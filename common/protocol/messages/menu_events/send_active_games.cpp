#include "./send_active_games.h"

SendActiveGamesMessage::SendActiveGamesMessage(std::vector<Match>&& matches): matches(matches) {}

void SendActiveGamesMessage::run() {}

SendActiveGamesMessage::~SendActiveGamesMessage() {}
