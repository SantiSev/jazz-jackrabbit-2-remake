#include "./client_protocol.h"

#include <vector>

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000

#define SEND_GAME_STATE 0x0100
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_UNJOIN_MATCH 0x0103
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
    const uint16_t id_match = recv_two_bytes();
    return std::make_unique<SendFinishMatchMessage>(id_match);
}

std::unique_ptr<SendGameStateMessage> ClientProtocol::recv_game_state() {
    return std::make_unique<SendGameStateMessage>();
}

std::unique_ptr<SendActiveGamesMessage> ClientProtocol::recv_active_games() {
    const uint8_t match_length = recv_one_byte();

    std::vector<Match> matches(match_length);
    for (size_t i = 0; i < match_length; i++) {
        const std::string name = recv_string();
        const uint8_t player = recv_one_byte();
        matches.push_back({name, player});
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

ClientProtocol::~ClientProtocol() {}
