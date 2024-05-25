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

ClientProtocol::~ClientProtocol() {}
