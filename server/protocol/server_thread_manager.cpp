#include "./server_thread_manager.h"

ServerThreadManager::ServerThreadManager(Socket&& skt):
        server_protocol(std::move(skt)), receiver(server_protocol), sender(server_protocol) {
    receiver.start();
    sender.start();
}

ServerThreadManager::~ServerThreadManager() {}
