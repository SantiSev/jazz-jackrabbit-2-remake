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
    Queue<std::shared_ptr<Message>> queue;

public:
    explicit ServerSender(ServerProtocol& protocol);

    bool is_dead();

    void stop() override;

    void run() override;

    ~ServerSender() override;

    Queue<std::shared_ptr<Message>>& get_sender_queue();
};

#endif
