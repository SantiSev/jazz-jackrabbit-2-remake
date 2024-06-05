#include "recv_active_games.h"

RecvActiveGames::RecvActiveGames(const MatchInfoDTO& dto):
        Message(RECV_ACTIVE_GAMES), active_games(dto) {}

void RecvActiveGames::run(MessageHandler& handler) {
    handler.handle_recv_active_games(active_games);
}

void RecvActiveGames::send_message(CommonProtocol& protocol) {
    protocol.send_active_games(header, active_games);
}

RecvActiveGames::~RecvActiveGames() = default;
