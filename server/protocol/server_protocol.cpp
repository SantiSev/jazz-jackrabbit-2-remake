#include "./server_protocol.h"

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const std::string ServerProtocol::recv_message() {
    uint8_t header;

    client.recvall(&header, sizeof(header), &was_closed);
    if (was_closed)
        return "";

    if (header == 0x00)
        return "CONNECTION_EVENT";
    else if (header == 0x01)
        return "IN_GAME_EVENT";
    else if (header == 0x02)
        return "MENU_EVENT";

    return "";
}

bool ServerProtocol::is_closed() const { return was_closed; }
