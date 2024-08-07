#ifndef _SERVER_RECEIVER_H
#define _SERVER_RECEIVER_H
#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "../../common/protocol/messages/common_message.h"
#include "./server_protocol.h"

class ServerReceiver: public Thread {
private:
    ServerProtocol& server_protocol;
    Queue<std::shared_ptr<Message>>& queue;

public:
    ServerReceiver(ServerProtocol& protocol, Queue<std::shared_ptr<Message>>& queue);

    bool is_dead();

    void stop() override;

    void run() override;

    ~ServerReceiver();

    bool isAlive();
};

#endif
