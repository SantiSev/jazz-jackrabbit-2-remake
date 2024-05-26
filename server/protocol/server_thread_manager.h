#include <memory>

#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerProtocol server_protocol;
    ServerReceiver receiver;
    ServerSender sender;

public:
    ServerThreadManager(Socket&& skt, Queue<std::unique_ptr<Message>>& receiver_queue);
    ~ServerThreadManager();
};
