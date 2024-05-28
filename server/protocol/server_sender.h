#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./server_protocol.h"

class ServerSender: public Thread {
private:
    ServerProtocol& server_protocol;
    Queue<std::shared_ptr<Message>>& queue;

public:
    ServerSender(ServerProtocol& protocol, Queue<std::shared_ptr<Message>>& queue);

    bool is_dead();

    void kill();

    void run() override;

    ~ServerSender();
};
