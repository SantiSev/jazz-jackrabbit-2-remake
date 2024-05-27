#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./server_protocol.h"

class ServerSender: public Thread {
private:
    ServerProtocol& server_protocol;
    Queue<int>& queue;

public:
    ServerSender(ServerProtocol& protocol, Queue<int>& queue);

    void run() override;

    ~ServerSender();
};
