#ifndef MESSAGE_RUNNER_H
#define MESSAGE_RUNNER_H

#include <memory>

#include "../../common/common_thread.h"

#include "client_message_handler.h"

class MessageRunner: public Thread {
private:
    ClientMessageHandler& message_handler;

public:
    Queue<std::shared_ptr<Message>> recv_message;

    explicit MessageRunner(ClientMessageHandler& message_handler);
    void run() override;
    ~MessageRunner() override;
};

#endif
