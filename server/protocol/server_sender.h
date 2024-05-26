#include "../../common/common_thread.h"
#include "./server_protocol.h"

class ServerSender: public Thread {
private:
    ServerProtocol& server_protocol;

public:
    explicit ServerSender(ServerProtocol& protocol);
    void run() override;
    ~ServerSender();
};
