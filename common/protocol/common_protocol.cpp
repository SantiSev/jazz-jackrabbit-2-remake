#include "./common_protocol.h"

#include <vector>

#include <arpa/inet.h>

CommonProtocol::CommonProtocol(Socket&& skt): skt(std::move(skt)), was_closed(false) {}

CommonProtocol::CommonProtocol(const std::string& hostname, const std::string& servname):
        skt(hostname.c_str(), servname.c_str()), was_closed(false) {}

const uint8_t CommonProtocol::recv_one_byte() {
    uint8_t one_byte;

    skt.recvall(&one_byte, sizeof(one_byte), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return one_byte;
}

const uint16_t CommonProtocol::recv_two_bytes() {
    uint16_t two_bytes;

    skt.recvall(&two_bytes, sizeof(two_bytes), &was_closed);
    if (was_closed)
        return CLOSE_CONNECTION;

    return ntohs(two_bytes);
}

const std::string CommonProtocol::recv_string() {
    uint8_t length;

    skt.recvall(&length, sizeof(length), &was_closed);

    std::vector<char> buf(length);
    skt.recvall(buf.data(), length, &was_closed);

    std::string result(buf.begin(), buf.end());

    return result;
}

void CommonProtocol::send_message(std::shared_ptr<BaseDTO> message) {
    skt.sendall(&(*message) + sizeof(BaseDTO) / 8, message->size(), &was_closed);
    if (was_closed)
        return;
}

CommonProtocol::~CommonProtocol() {}
