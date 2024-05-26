#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_LEAVE_MATCH 0x0103
#define SEND_FINISH_MATCH 0x0104

#define SEND_ACTIVE_GAMES 0x0200
#define RECV_CREATE_GAME 0x0201
#define SEND_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203

ClientProtocol::ClientProtocol(const std::string& hostname, const std::string& servname):
        server(hostname.c_str(), servname.c_str()), was_closed(false) {}

const uint8_t ClientProtocol::recv_one_byte() {
    uint8_t one_byte;

    server.recvall(&one_byte, sizeof(one_byte), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return one_byte;
}

const uint16_t ClientProtocol::recv_two_bytes() {
    uint16_t two_bytes;

    server.recvall(&two_bytes, sizeof(two_bytes), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return ntohs(two_bytes);
}

const std::string ClientProtocol::recv_string() {
    uint8_t length;

    server.recvall(&length, sizeof(length), &was_closed);
    length = ntohs(length);

    std::vector<char> buf(length);
    server.recvall(buf.data(), length, &was_closed);

    std::string result(buf.begin(), buf.end());

    return result;
}

std::unique_ptr<SendFinishMatchMessage> ClientProtocol::recv_finish_match() {
    return std::make_unique<SendFinishMatchMessage>();
}

std::unique_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    return std::make_unique<SendGameStateMessage>();
}

std::unique_ptr<SendActiveGamesMessage> ClientProtocol::recv_active_games() {
    const uint8_t match_length = recv_one_byte();

    std::vector<Match> matches(match_length);
    for (size_t i = 0; i < match_length; i++) {
        const std::string name = recv_string();
        const uint8_t players = recv_one_byte();
        matches.push_back({name, players});
    }

    return std::make_unique<SendActiveGamesMessage>(std::move(matches));
}

std::unique_ptr<SendGameCreatedMessage> ClientProtocol::recv_game_created() {
    return std::make_unique<SendGameCreatedMessage>();
}

std::unique_ptr<Message> ClientProtocol::recv_message() {
    const uint16_t header = recv_two_bytes();

    switch (header) {
        case CLOSE_CONNECTION:
            return std::make_unique<CloseConnectionMessage>();
        case SEND_FINISH_MATCH:
            return recv_finish_match();
        case SEND_GAME_STATE:
            return recv_game_state();
        case SEND_ACTIVE_GAMES:
            return recv_active_games();
        case SEND_GAME_CREATED:
            return recv_game_created();
        default:
            return std::make_unique<InvalidMessage>();
    }
}

void ClientProtocol::send_command(uint16_t id_player, uint8_t id_command) {
    uint16_t header = htons(RECV_COMMAND);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    server.sendall(&id_command, sizeof(id_command), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_cheat_command(uint16_t id_player, uint8_t id_cheat_command) {
    uint16_t header = htons(RECV_CHEAT_COMMAND);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    server.sendall(&id_cheat_command, sizeof(id_cheat_command), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_leave_match(uint16_t id_player) {
    uint16_t header = htons(RECV_LEAVE_MATCH);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_create_game(uint16_t id_player, std::string& match_name) {
    uint16_t header = htons(RECV_CREATE_GAME);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    uint8_t length = match_name.length();
    server.sendall(&length, sizeof(length), &was_closed);
    if (was_closed)
        return;

    server.sendall(match_name.data(), length, &was_closed);
    if (was_closed)
        return;
}

void ClientProtocol::send_join_match(uint16_t id_player, uint16_t id_match,
                                     uint8_t player_character) {
    uint16_t header = htons(RECV_JOIN_MATCH);
    server.sendall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return;

    id_player = htons(id_player);
    server.sendall(&id_player, sizeof(id_player), &was_closed);
    if (was_closed)
        return;

    id_match = htons(id_match);
    server.sendall(&id_match, sizeof(id_match), &was_closed);
    if (was_closed)
        return;

    server.sendall(&player_character, sizeof(player_character), &was_closed);
    if (was_closed)
        return;
}

ClientProtocol::~ClientProtocol() {}
