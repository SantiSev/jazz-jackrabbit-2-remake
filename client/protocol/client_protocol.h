#include <memory>
#include <string>

#include "../../common/common_socket.h"
#include "./messages/client_message.h"

class ClientProtocol {
private:
    Socket server;

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    std::shared_ptr<Message> recv_message();

    ~ClientProtocol();
};
