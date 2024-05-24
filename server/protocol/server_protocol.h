#include <map>
#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "./server_message.h"

class ServerProtocol {
private:
    Socket client;
    bool was_closed;

public:
    explicit ServerProtocol(Socket&& skt);

    std::shared_ptr<Message> recv_message();

    bool is_closed() const;
};
