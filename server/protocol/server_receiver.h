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
    std::shared_ptr<Queue<std::shared_ptr<Message>>>& queue;

public:
    ServerReceiver(ServerProtocol& protocol,
                   std::shared_ptr<Queue<std::shared_ptr<Message>>>& queue);

    bool is_dead();

    void kill();

    void run() override;

    std::shared_ptr<Queue<std::shared_ptr<Message>>>& get_receiver_queue();

    ~ServerReceiver();

    void change_receiver_queue(std::shared_ptr<Queue<std::shared_ptr<Message>>>& sharedPtr);
};

#endif
