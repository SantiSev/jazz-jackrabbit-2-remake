#include <cstdint>
#include <string>

#include "../common_socket.h"

class CommonProtocol {
protected:
    bool was_closed;
    Socket skt;

    const uint8_t recv_one_byte();
    const uint16_t recv_two_bytes();
    const std::string recv_string();

public:
    explicit CommonProtocol(Socket&& skt);
    CommonProtocol(const std::string& hostname, const std::string& servname);
    ~CommonProtocol();
};
