#ifndef TP_FINAL_CLIENT_RECEIVER_H
#define TP_FINAL_CLIENT_RECEIVER_H

#include <memory>

#include "../../common/common_queue.h"
#include "../../common/common_thread.h"
#include "./client_protocol.h"

class ClientReceiver: public Thread {
private:
    ClientProtocol& client_protocol;
    Queue<std::shared_ptr<Message>>& queue;

public:
    ClientReceiver(ClientProtocol& client_protocol, Queue<std::shared_ptr<Message>>& queue);

    bool is_dead();

    void stop() override;

    void run() override;

    ~ClientReceiver();
};

#endif
