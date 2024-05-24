#include "./server_protocol.h"

#include <arpa/inet.h>

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {
    events[0x0000] = "CLOSE_CONNECTION";
    events[0x0101] = "RECV_COMMAND";
    events[0x0102] = "RECV_CHEAT_COMMAND";
    events[0x0103] = "RECV_UNJOIN_MATCH";
    events[0x0201] = "RECV_CREATE_GAME";
    events[0x0202] = "RECV_GAME_CREATED";
    events[0x0203] = "RECV_JOIN_MATCH";
}

const std::string ServerProtocol::deserialize_header(uint16_t header) { return events[header]; }

const std::string ServerProtocol::recv_message() {
    uint16_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    header = ntohs(header);
    if (was_closed)
        return "";

    return deserialize_header(header);
}

bool ServerProtocol::is_closed() const { return was_closed; }
