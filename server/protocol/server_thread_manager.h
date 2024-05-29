#ifndef _SERVER_THREAD_MANAGER_H
#define _SERVER_THREAD_MANAGER_H
#include <memory>

#include "./server_receiver.h"
#include "./server_sender.h"

class ServerThreadManager {
private:
    ServerProtocol server_protocol;
    ServerReceiver receiver;
    ServerSender sender;

public:
    ServerThreadManager(Socket&& skt,
                        std::shared_ptr<Queue<std::shared_ptr<Message>>>& receiver_queue,
                        std::shared_ptr<Queue<std::shared_ptr<Message>>>& sender_queue);

    std::shared_ptr<Queue<std::shared_ptr<Message>>> get_receiver_queue();

    std::shared_ptr<Queue<std::shared_ptr<Message>>> get_sender_queue();

    void set_receiver_queue(std::shared_ptr<Queue<std::shared_ptr<Message>>> receiver_queue);

    void set_sender_queue(std::shared_ptr<Queue<std::shared_ptr<Message>>> sender_queue);

    void stop();

    ~ServerThreadManager();
};

#endif
