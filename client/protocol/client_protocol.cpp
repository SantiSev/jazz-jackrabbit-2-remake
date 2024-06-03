#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>


ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        CommonProtocol(hostname, servname), my_client_id(0), my_player_id(0) {}

std::shared_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    FinishMatchDTO finish_match = {};
    skt.recvall(&finish_match, sizeof(finish_match), &was_closed);
    return std::make_shared<SendFinishMatchMessage>(finish_match);
}

std::shared_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    GameStateDTO game_state = {};
    skt.recvall(&game_state, sizeof(game_state), &was_closed);
    return std::make_shared<SendGameStateMessage>(game_state);
}

std::shared_ptr<SendActiveGamesMessage> ClientProtocol::recv_active_games() {
    ActiveGamesDTO active_games = {};
    skt.recvall(&active_games, sizeof(active_games), &was_closed);
    return std::make_shared<SendActiveGamesMessage>(active_games);
}

std::shared_ptr<SendGameCreatedMessage> ClientProtocol::recv_game_created() {
    GameCreatedDTO game_created = {};
    skt.recvall(&game_created, sizeof(game_created), &was_closed);
    return std::make_shared<SendGameCreatedMessage>(game_created);
}

std::shared_ptr<AcptConnection> ClientProtocol::recv_acpt_connection() {
    uint16_t id_client = recv_two_bytes();
    return std::make_shared<AcptConnection>(id_client);
}

std::shared_ptr<Message> ClientProtocol::recv_message() {
    const uint16_t header = recv_two_bytes();

    switch (header) {
        case CLOSE_CONNECTION:
            return std::make_shared<CloseConnectionMessage>();
        case SEND_FINISH_MATCH:
            return recv_finish_match();
        case SEND_GAME_STATE:
            return recv_game_state();
        case SEND_ACTIVE_GAMES:
            return recv_active_games();
        case SEND_GAME_CREATED:
            return recv_game_created();
        case ACPT_CONNECTION:
            return recv_acpt_connection();
        default:
            return std::make_shared<InvalidMessage>();
    }
}

void ClientProtocol::set_my_client_id(const id_client_t& new_client_id) {
    my_client_id = new_client_id;
}

uint16_t ClientProtocol::get_client_id() const { return my_client_id; }

void ClientProtocol::set_my_player_id(const id_player_t& new_player_id) {
    my_player_id = new_player_id;
}
uint16_t ClientProtocol::get_player_id() const { return my_player_id; }

ClientProtocol::~ClientProtocol() {}
