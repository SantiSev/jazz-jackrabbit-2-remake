#include <memory>

#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerProtocol server_protocol;
    ServerReceiver receiver;
    ServerSender sender;

public:
    ServerThreadManager(Socket&& skt, Queue<std::shared_ptr<Message>>& receiver_queue,
                        Queue<std::shared_ptr<Message>>& sender_queue);
    ~ServerThreadManager();
};
