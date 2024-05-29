#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./client_protocol.h"

class ClientSender: public Thread {
private:
    ClientProtocol& client_protocol;
    Queue<std::shared_ptr<Message>>& queue;

public:
    explicit ClientSender(ClientProtocol& client_protocol, Queue<std::shared_ptr<Message>>& queue);

    bool is_dead();

    void kill();

    void run() override;

    ~ClientSender();
};