#ifndef _SERVER_SENDER_H
#define _SERVER_SENDER_H
#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
//#include "../../common/protocol/messages/common_message.h"

#include "server_protocol.h"

class ServerSender: public Thread {
private:
    ServerProtocol& server_protocol;
    std::shared_ptr<Queue<std::shared_ptr<Message>>> queue;

public:
    explicit ServerSender(ServerProtocol& protocol);

    bool is_dead();

    void stop() override;

    void run() override;

    ~ServerSender() override;

    std::shared_ptr<Queue<std::shared_ptr<Message>>>& get_sender_queue();

    void change_sender_queue(const std::shared_ptr<Queue<std::shared_ptr<Message>>>& new_queue);
};

#endif
