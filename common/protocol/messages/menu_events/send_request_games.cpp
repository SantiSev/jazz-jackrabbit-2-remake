#include "./send_request_games.h"

SendRequestGamesMessage::SendRequestGamesMessage(const RequestActiveGamesDTO& active_games):
        Message(RECV_REQUEST_ACTIVE_GAMES), active_games(active_games) {}

void SendRequestGamesMessage::run(MessageHandler& handler) {
    handler.handle_request_active_games(active_games);
}

void SendRequestGamesMessage::send_message(CommonProtocol& protocol) {
    protocol.send_request_active_games(header, active_games);
}

SendRequestGamesMessage::~SendRequestGamesMessage() = default;
