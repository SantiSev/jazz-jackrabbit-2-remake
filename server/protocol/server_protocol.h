#include <map>
#include <string>

#include "../../common/common_socket.h"

class ServerProtocol {
private:
    Socket client;
    bool was_closed;
    std::map<uint16_t, std::string> events;

    const std::string deserialize_header(uint16_t header);

public:
    explicit ServerProtocol(Socket&& skt);

    const std::string recv_message();

    bool is_closed() const;
};
