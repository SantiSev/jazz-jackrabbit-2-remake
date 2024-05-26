#include "../common_socket.h"

class CommonProtocol {
private:
    Socket skt;
    bool was_closed;

public:
    CommonProtocol();
    ~CommonProtocol();
};
