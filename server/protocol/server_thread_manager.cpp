#include "./server_thread_manager.h"

ServerThreadManager::ServerThreadManager(
        Socket&& skt, std::shared_ptr<Queue<std::shared_ptr<Message>>>& receiver_queue):
        server_protocol(std::move(skt)),
        receiver(server_protocol, receiver_queue),
        sender(server_protocol) {
    receiver.start();
    sender.start();
}

ServerThreadManager::~ServerThreadManager() = default;

std::shared_ptr<Queue<std::shared_ptr<Message>>> ServerThreadManager::get_receiver_queue() {
    return receiver.get_receiver_queue();
}

std::shared_ptr<Queue<std::shared_ptr<Message>>>& ServerThreadManager::get_sender_queue() {
    return sender.get_sender_queue();
}

void ServerThreadManager::set_receiver_queue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& receiver_queue) {
    receiver.change_receiver_queue(receiver_queue);
}

void ServerThreadManager::set_sender_queue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& sender_queue) {
    sender.change_sender_queue(sender_queue);
}

void ServerThreadManager::stop() {
    sender.stop();
    sender.join();
    receiver.stop();
    receiver.join();
}

void ServerThreadManager::set_client_id(const size_t& new_id) { this->client_id = new_id; }

size_t ServerThreadManager::get_client_id() const { return client_id; }
