#include "../../common/common_thread.h"
#include "./client_protocol.h"

class ClientSender: public Thread {
private:
    ClientProtocol& client_protocol;

public:
    explicit ClientSender(ClientProtocol& client_protocol);
    void run() override;
    ~ClientSender();
};
