#include <string>

#include "../../common/common_socket.h"

class ClientProtocol {
private:
    Socket server;

public:
    ClientProtocol(const std::string& hostname, const std::string& servname);

    ~ClientProtocol();
};
