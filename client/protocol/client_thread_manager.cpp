#include "./client_thread_manager.h"

ClientThreadManager::ClientThreadManager(const std::string& hostname, const std::string& servname,
                                         Queue<std::shared_ptr<Message>>& receiver_queue,
                                         Queue<int>& sender_queue):
        client_protocol(hostname, servname),
        receiver(client_protocol, receiver_queue),
        sender(client_protocol, sender_queue) {
    receiver.start();
    sender.start();
}

ClientThreadManager::~ClientThreadManager() {
    receiver.join();
    receiver.kill();
    sender.join();
    sender.kill();
}
