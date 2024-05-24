#include "./server_protocol.h"

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_UNJOIN_MATCH 0x0103
#define RECV_CREATE_GAME 0x0201
#define RECV_GAME_CREATED 0x0202
#define RECV_JOIN_MATCH 0x0203

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const std::string ServerProtocol::recv_message() {
    uint16_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    header = ntohs(header);
    if (was_closed)
        return "";

    switch (header) {
        case CLOSE_CONNECTION:
            break;
        case RECV_COMMAND:
            break;
        case RECV_UNJOIN_MATCH:
            break;
        case RECV_CREATE_GAME:
            break;
        case RECV_GAME_CREATED:
            break;
        case RECV_JOIN_MATCH:
            break;
    }

    return "";
}

bool ServerProtocol::is_closed() const { return was_closed; }
