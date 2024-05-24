#include <string>

#include "../../common/common_socket.h"

class ServerProtocol {
private:
    Socket client;
    bool was_closed;

public:
    explicit ServerProtocol(Socket&& skt);

    const std::string recv_message();

    bool is_closed() const;
};
