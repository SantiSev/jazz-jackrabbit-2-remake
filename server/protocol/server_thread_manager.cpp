#include "./server_thread_manager.h"

ServerThreadManager::ServerThreadManager(Socket&& skt,
                                         Queue<std::unique_ptr<Message>>& receiver_queue,
                                         Queue<int>& sender_queue):
        server_protocol(std::move(skt)),
        receiver(server_protocol, receiver_queue),
        sender(server_protocol, sender_queue) {
    receiver.start();
    sender.start();
}

ServerThreadManager::~ServerThreadManager() {
    receiver.kill();
    receiver.join();
}
