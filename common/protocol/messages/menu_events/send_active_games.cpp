#include "./send_active_games.h"

SendActiveGamesMessage::SendActiveGamesMessage(ActiveGamesDTO& active_games):
        Message(SEND_ACTIVE_GAMES), active_games(active_games) {}

void SendActiveGamesMessage::run() {}

void SendActiveGamesMessage::send_message(CommonProtocol& protocol) {
    protocol.send_active_games(header, active_games);
}

SendActiveGamesMessage::~SendActiveGamesMessage() {}
