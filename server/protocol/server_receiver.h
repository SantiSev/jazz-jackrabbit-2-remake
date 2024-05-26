#include "../../common/common_thread.h"
#include "./server_protocol.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol server_protocol;

public:
    explicit ServerReceiver(Socket&& skt);
    ~ServerReceiver();
};
