#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>

#include "../../common/protocol/messages/menu_events/send_connected_to_game.h"


ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        CommonProtocol(hostname, servname) {}

std::shared_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    FinishMatchDTO finish_match = {};
    skt.recvall(&finish_match, sizeof(finish_match), &was_closed);
    return std::make_shared<SendFinishMatchMessage>(finish_match);
}

std::shared_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    GameStateDTO game_state = {};
    skt.recvall(&game_state, sizeof(game_state), &was_closed);
    game_state.seconds = ntohs(game_state.seconds);
    for (int i = 0; i < game_state.num_players; i++) {
        game_state.players[i].id = ntohs(game_state.players[i].id);
        game_state.players[i].health = ntohs(game_state.players[i].health);
        game_state.players[i].points = ntohs(game_state.players[i].points);
        game_state.players[i].x_pos = ntohs(game_state.players[i].x_pos);
        game_state.players[i].y_pos = ntohs(game_state.players[i].y_pos);
        for (int j = 0; j < NUM_OF_WEAPONS; j++) {
            game_state.players[i].weapons[j].ammo = ntohs(game_state.players[i].weapons[j].ammo);
        }
    }
    for (int i = 0; i < game_state.num_enemies; i++) {
        game_state.enemies[i].x_pos = ntohs(game_state.enemies[i].x_pos);
        game_state.enemies[i].y_pos = ntohs(game_state.enemies[i].y_pos);
    }
    return std::make_shared<SendGameStateMessage>(game_state);
}

std::shared_ptr<SendRequestGamesMessage> ClientProtocol::recv_active_games() {
    RequestActiveGamesDTO active_games = {};
    skt.recvall(&active_games, sizeof(active_games), &was_closed);
    active_games.id_client = ntohs(active_games.id_client);
    return std::make_shared<SendRequestGamesMessage>(active_games);
}

std::shared_ptr<SendConnectedToGameMessage> ClientProtocol::recv_game_created() {
    ClientHasConnectedToMatchDTO game_created = {};
    skt.recvall(&game_created, sizeof(game_created), &was_closed);
    game_created.id_player = ntohs(game_created.id_player);
    return std::make_shared<SendConnectedToGameMessage>(game_created);
}

std::shared_ptr<AcptConnection> ClientProtocol::recv_acpt_connection() {
    uint16_t id_client = recv_two_bytes();
    return std::make_shared<AcptConnection>(id_client);
}

std::shared_ptr<Message> ClientProtocol::recv_game_joined() {
    ClientHasConnectedToMatchDTO game_joined = {};
    skt.recvall(&game_joined, sizeof(game_joined), &was_closed);
    game_joined.id_player = ntohs(game_joined.id_player);
    return std::make_shared<SendConnectedToGameMessage>(game_joined);
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
        case RECV_ACTIVE_GAMES:
            return recv_active_games();
        case SEND_GAME_CREATED:
            return recv_game_created();
        case ACPT_CONNECTION:
            return recv_acpt_connection();
        case SEND_GAME_JOINED:
            return recv_game_joined();
        default:
            return std::make_shared<InvalidMessage>();
    }
}

ClientProtocol::~ClientProtocol() = default;
