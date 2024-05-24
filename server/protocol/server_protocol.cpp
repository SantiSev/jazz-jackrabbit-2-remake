#include "./server_protocol.h"

#include <arpa/inet.h>

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const std::string ServerProtocol::recv_message() {
    uint16_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    header = ntohs(header);
    if (was_closed)
        return "";

    if (header == 0x0000)
        return "CLOSE_CONNECTION";
    else if (header == 0x0101)
        return "RECV_COMMAND";
    else if (header == 0x0102)
        return "RECV_CHEAT_COMMAND";
    else if (header == 0x0103)
        return "RECV_UNJOIN_MATCH";
    else if (header == 0x0201)
        return "RECV_CREATE_GAME";
    else if (header == 0x0202)
        return "RECV_GAME_CREATED";
    else if (header == 0x0203)
        return "RECV_JOIN_MATCH";

    return "";
}

bool ServerProtocol::is_closed() const { return was_closed; }
