#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerReceiver* receiver;
    ServerSender* sender;

public:
    ServerThreadManager();
    ~ServerThreadManager();
};
