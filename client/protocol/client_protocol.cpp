#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        CommonProtocol(hostname, servname) {}

std::shared_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    return std::make_shared<SendFinishMatchMessage>();
}

std::shared_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    return std::make_shared<SendGameStateMessage>();
}

std::shared_ptr<SendActiveGamesMessage> ClientProtocol::recv_active_games() {
    const uint8_t match_length = recv_one_byte();

    std::vector<Match> matches(match_length);
    for (size_t i = 0; i < match_length; i++) {
        const std::string name = recv_string();
        const uint8_t players = recv_one_byte();
        matches.push_back({name, players});
    }

    return std::make_shared<SendActiveGamesMessage>(std::move(matches));
}

std::shared_ptr<SendGameCreatedMessage> ClientProtocol::recv_game_created() {
    return std::make_shared<SendGameCreatedMessage>();
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
        default:
            return std::make_shared<InvalidMessage>();
    }
}

void ClientProtocol::send_command(uint16_t id_player, uint8_t id_command) {
    uint16_t header = htons(RECV_COMMAND);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    skt.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    skt.sendall(&id_command, sizeof(id_command), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_cheat_command(uint16_t id_player, uint8_t id_cheat_command) {
    uint16_t header = htons(RECV_CHEAT_COMMAND);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    skt.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    skt.sendall(&id_cheat_command, sizeof(id_cheat_command), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_leave_match(uint16_t id_player) {
    uint16_t header = htons(RECV_LEAVE_MATCH);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    skt.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_create_game(uint16_t id_player, std::string& match_name) {
    uint16_t header = htons(RECV_CREATE_GAME);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    skt.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    uint8_t length = match_name.length();
    skt.sendall(&length, sizeof(length), &was_closed);
    if (was_closed)
        return;

    skt.sendall(match_name.data(), length, &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_join_match(uint16_t id_player, uint16_t id_match,
                                     uint8_t player_character) {
    uint16_t header = htons(RECV_JOIN_MATCH);
    skt.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    skt.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    id_match = htons(id_match);
    skt.sendall(&id_match, sizeof(id_match), &was_closed);
    if (was_closed)
        return;

    skt.sendall(&player_character, sizeof(player_character), &was_closed);
    if (was_closed)
        return;
}

ClientProtocol::~ClientProtocol() {}
