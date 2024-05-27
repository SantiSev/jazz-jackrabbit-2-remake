#include "./client_thread_manager.h"

ClientThreadManager::ClientThreadManager(const std::string& hostname, const std::string& servname):
        client_protocol(hostname, servname), receiver(client_protocol), sender(client_protocol) {
    receiver.start();
    sender.start();
}

ClientThreadManager::~ClientThreadManager() {
    receiver.join();
    sender.join();
}
