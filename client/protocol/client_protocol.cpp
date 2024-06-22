#include "./client_protocol.h"

#include <arpa/inet.h>
#include <endian.h>

#include "../../common/common_liberror.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        CommonProtocol(hostname, servname) {}

std::shared_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    FinishMatchDTO finish_match = {};
    skt.recvall(&finish_match, sizeof(finish_match), &was_closed);
    return std::make_shared<SendFinishMatchMessage>();
}

std::shared_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    GameStateDTO game_state = {};
    skt.recvall(&game_state, sizeof(game_state), &was_closed);
    game_state.seconds = ntohs(game_state.seconds);
    for (size_t i = 0; i < game_state.num_players; i++) {
        game_state.players[i].id = ntohs(game_state.players[i].id);
        game_state.players[i].health = ntohs(game_state.players[i].health);
        game_state.players[i].points = ntohs(game_state.players[i].points);
        game_state.players[i].x_pos = ntohs(game_state.players[i].x_pos);
        game_state.players[i].y_pos = ntohs(game_state.players[i].y_pos);
        for (int j = 0; j < NUM_OF_WEAPONS; j++) {
            game_state.players[i].weapons[j].ammo = ntohs(game_state.players[i].weapons[j].ammo);
        }
    }
    for (size_t i = 0; i < game_state.num_enemies; i++) {
        game_state.enemies[i].id = ntohs(game_state.enemies[i].id);
        game_state.enemies[i].x_pos = ntohs(game_state.enemies[i].x_pos);
        game_state.enemies[i].y_pos = ntohs(game_state.enemies[i].y_pos);
    }
    for (size_t i = 0; i < game_state.num_bullets; i++) {
        game_state.bullets[i].id = be64toh(game_state.bullets[i].id);
        game_state.bullets[i].x_pos = ntohs(game_state.bullets[i].x_pos);
        game_state.bullets[i].y_pos = ntohs(game_state.bullets[i].y_pos);
    }
    return std::make_shared<SendGameStateMessage>(game_state);
}

std::shared_ptr<RecvActiveGames> ClientProtocol::recv_active_games() {
    MatchInfoDTO active_games = {};
    skt.recvall(&active_games, sizeof(active_games), &was_closed);
    for (int i = 0; i < active_games.num_games; i++) {
        active_games.active_games[i].map_id = ntohs(active_games.active_games[i].map_id);
    }
    return std::make_shared<RecvActiveGames>(active_games);
}

std::shared_ptr<SendConnectedToGameMessage> ClientProtocol::recv_game_created() {
    ClientHasConnectedToMatchDTO game_created = {};
    skt.recvall(&game_created, sizeof(game_created), &was_closed);
    game_created.map_id = ntohs(game_created.map_id);
    return std::make_shared<SendConnectedToGameMessage>(game_created);
}

std::shared_ptr<AcptConnection> ClientProtocol::recv_acpt_connection() {
    uint16_t id_client = recv_two_bytes();
    return std::make_shared<AcptConnection>(id_client);
}

std::shared_ptr<Message> ClientProtocol::recv_game_joined() {
    ClientHasConnectedToMatchDTO game_joined = {};
    skt.recvall(&game_joined, sizeof(game_joined), &was_closed);
    game_joined.map_id = ntohs(game_joined.map_id);
    return std::make_shared<SendConnectedToGameMessage>(game_joined);
}

std::shared_ptr<Message> ClientProtocol::recv_message() {
    try {
        const uint16_t header = recv_two_bytes();

        switch (header) {
            case CLOSE_CONNECTION:
                return recv_closed_connection();
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
    } catch (const LibError& e) {
        force_shutdown();
    }
    return std::make_shared<InvalidMessage>();
}

bool ClientProtocol::is_closed() const { return was_closed; }

ClientProtocol::~ClientProtocol() = default;
