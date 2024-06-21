#include "./client_protocol.h"

#include <iostream>

#include <arpa/inet.h>
#include <endian.h>

#include "../../common/common_liberror.h"

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        CommonProtocol(hostname, servname) {}

std::shared_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    std::cout << "about to receive finish match" << std::endl;
    return std::make_shared<SendFinishMatchMessage>();
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
        game_state.enemies[i].id = ntohs(game_state.enemies[i].id);
        game_state.enemies[i].x_pos = ntohs(game_state.enemies[i].x_pos);
        game_state.enemies[i].y_pos = ntohs(game_state.enemies[i].y_pos);
    }
    for (int i = 0; i < game_state.num_bullets; i++) {
        game_state.bullets[i].id = be64toh(game_state.bullets[i].id);
        game_state.bullets[i].x_pos = ntohs(game_state.bullets[i].x_pos);
        game_state.bullets[i].y_pos = ntohs(game_state.bullets[i].y_pos);
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
    std::cout << "game created" << std::endl;
    return std::make_shared<SendConnectedToGameMessage>(game_created);
}

std::shared_ptr<AcptConnection> ClientProtocol::recv_acpt_connection() {
    uint16_t id_client = recv_two_bytes();
    return std::make_shared<AcptConnection>(id_client);
}

std::shared_ptr<Message> ClientProtocol::recv_message() {
    try {
        const uint16_t header = recv_two_bytes();
        if (header != 0x0100) {
            std::cout << "header: " << header << std::endl;
        }

        switch (header) {
            case CLOSE_CONNECTION:
                return recv_closed_connection();
            case SEND_FINISH_MATCH:
                return recv_finish_match();
            case SEND_GAME_STATE:
                return recv_game_state();
            case RECV_ACTIVE_GAMES:
                return recv_active_games();
            case SEND_CONNECTED_TO_MATCH:
                return recv_game_created();
            case ACPT_CONNECTION:
                return recv_acpt_connection();
            default:
                CloseConnectionDTO dto = {};
                return std::make_shared<CloseConnectionMessage>(dto);
        }
    } catch (const LibError& e) {
        force_shutdown();
        CloseConnectionDTO dto = {};
        return std::make_shared<CloseConnectionMessage>(dto);
    }
    return std::make_shared<InvalidMessage>();
}

bool ClientProtocol::is_closed() const { return was_closed; }

ClientProtocol::~ClientProtocol() = default;
