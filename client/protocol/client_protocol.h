#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "./messages/client_message.h"

class ClientProtocol {
private:
    Socket server;
    bool was_closed;

    const uint8_t recv_one_byte();
    const uint16_t recv_two_bytes();
    const std::string recv_string();

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    std::shared_ptr<Message> recv_message();

    ~ClientProtocol();
};
