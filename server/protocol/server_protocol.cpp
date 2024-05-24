#include "./server_protocol.h"

ServerProtocol::ServerProtocol(Socket&& skt): client(std::move(skt)), was_closed(false) {}

const std::string ServerProtocol::recv_msg() {
    uint8_t data;

    client.recvall(&data, sizeof(data), &was_closed);
    if (was_closed)
        return "";

    if (data == 0x00)
        return "CONNECTION_EVENT";
    else if (data == 0x01)
        return "IN_GAME_EVENT";
    else if (data == 0x02)
        return "MENU_EVENT";

    return "";
}

bool ServerProtocol::is_closed() const { return was_closed; }
