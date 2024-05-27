#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./server_protocol.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& server_protocol;
    Queue<std::unique_ptr<Message>>& queue;

public:
    ServerReceiver(ServerProtocol& protocol, Queue<std::unique_ptr<Message>>& queue);

    bool is_dead();

    void kill();

    void run() override;

    ~ServerReceiver();
};
