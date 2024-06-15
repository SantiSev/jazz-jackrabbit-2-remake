#include "./server_thread_manager.h"

ServerThreadManager::ServerThreadManager(Socket&& skt,
                                         Queue<std::shared_ptr<Message>>& receiver_queue):
        server_protocol(std::move(skt)),
        receiver(server_protocol, receiver_queue),
        sender(server_protocol) {
    receiver.start();
    sender.start();
}

ServerThreadManager::~ServerThreadManager() = default;

Queue<std::shared_ptr<Message>>& ServerThreadManager::get_sender_queue() {
    return sender.get_sender_queue();
}

void ServerThreadManager::stop() {
    receiver.stop();
    sender.stop();
#ifdef LOG_VERBOSE
    std::cout << "sender and receiver stopped" << std::endl;
#endif
    server_protocol.force_shutdown();
#ifdef LOG_VERBOSE
    std::cout << "protocol shutdown" << std::endl;
#endif
    sender.join();
    receiver.join();
#ifdef LOG_VERBOSE
    std::cout << "sender and receiver joined" << std::endl;
#endif
}

void ServerThreadManager::set_client_id(const uint16_t& new_id) { this->client_id = new_id; }

id_client_t ServerThreadManager::get_client_id() const { return client_id; }

int ServerThreadManager::get_current_match_id() const { return match_joined_id; }

void ServerThreadManager::set_match_joined_id(const int& new_id) { this->match_joined_id = new_id; }
