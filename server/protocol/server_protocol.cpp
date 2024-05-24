#include "./server_protocol.h"

#include <arpa/inet.h>

#define CLOSE_CONNECTION 0x0000
#define RECV_COMMAND 0x0101
#define RECV_CHEAT_COMMAND 0x0102
#define RECV_UNJOIN_MATCH 0x0103
#define RECV_CREATE_GAME 0x0201
#define RECV_JOIN_MATCH 0x0203

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const uint16_t ServerProtocol::recv_header() {
    uint16_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    header = ntohs(header);
    if (was_closed)
        return CLOSE_CONNECTION;

    return header;
}

std::shared_ptr<Message> ServerProtocol::recv_message() {
    const uint16_t header = recv_header();

    switch (header) {
        case CLOSE_CONNECTION:
            return std::make_shared<CloseConnectionMessage>();
        case RECV_COMMAND:
            return std::make_shared<RecvCommandMessage>();
        case RECV_CHEAT_COMMAND:
            return std::make_shared<RecvCheatCommandMessage>();
        case RECV_UNJOIN_MATCH:
            return std::make_shared<RecvUnjoinMatchMessage>();
        case RECV_CREATE_GAME:
            return std::make_shared<RecvCreateGameMessage>();
        case RECV_JOIN_MATCH:
            return std::make_shared<RecvJoinMatchMessage>();
    }

    return NULL;
}

bool ServerProtocol::is_closed() const { return was_closed; }
