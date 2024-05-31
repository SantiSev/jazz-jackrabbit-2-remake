#ifndef _COMMON_PROTOCOL_H
#define _COMMON_PROTOCOL_H

#include <cstdint>
#include <memory>
#include <string>

#include "../common_socket.h"
#include "./common_dto.h"

class CommonProtocol {
protected:
    Socket skt;
    bool was_closed;

    const uint8_t recv_one_byte();
    const uint16_t recv_two_bytes();
    const std::string recv_string();

public:
    explicit CommonProtocol(Socket&& skt);
    CommonProtocol(const std::string& hostname, const std::string& servname);
    void send_message(std::shared_ptr<BaseDTO> message);
    ~CommonProtocol();
};

#endif
