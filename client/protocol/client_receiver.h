#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./client_protocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& client_protocol;
    Queue<std::unique_ptr<Message>>& queue;

public:
    ClientReceiver(ClientProtocol& client_protocol, Queue<std::unique_ptr<Message>>& queue);
    void run() override;
    ~ClientReceiver();
};
