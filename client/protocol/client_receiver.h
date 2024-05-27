#include "../../common/common_thread.h"
#include "./client_protocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& client_protocol;

public:
    explicit ClientReceiver(ClientProtocol& client_protocol);
    ~ClientReceiver();
};
