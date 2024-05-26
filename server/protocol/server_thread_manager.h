#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerProtocol server_protocol;
    ServerReceiver receiver;
    ServerSender sender;

public:
    explicit ServerThreadManager(Socket&& skt);
    ~ServerThreadManager();
};
