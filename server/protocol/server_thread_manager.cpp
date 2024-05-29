#include "./server_thread_manager.h"

ServerThreadManager::ServerThreadManager(
        Socket&& skt, std::shared_ptr<Queue<std::shared_ptr<Message>>>& receiver_queue,
        std::shared_ptr<Queue<std::shared_ptr<Message>>>& sender_queue):
        server_protocol(std::move(skt)),
        receiver(server_protocol, receiver_queue),
        sender(server_protocol, sender_queue) {
    receiver.start();
    sender.start();
}

ServerThreadManager::~ServerThreadManager() {
    //    receiver.kill();
    //    receiver.join();
    //    sender.kill();
    //    sender.join();
}

std::shared_ptr<Queue<std::shared_ptr<Message>>> ServerThreadManager::get_receiver_queue() {
    return receiver.get_receiver_queue();
}

std::shared_ptr<Queue<std::shared_ptr<Message>>> ServerThreadManager::get_sender_queue() {
    return sender.get_sender_queue();
}

void ServerThreadManager::set_receiver_queue(
        std::shared_ptr<Queue<std::shared_ptr<Message>>> receiver_queue) {
    receiver.change_receiver_queue(receiver_queue);
}

void ServerThreadManager::set_sender_queue(
        std::shared_ptr<Queue<std::shared_ptr<Message>>> sender_queue) {
    sender.change_sender_queue(sender_queue);
}

void ServerThreadManager::stop() {
    server_protocol.force_shutdown();
    receiver.kill();
    receiver.join();
    sender.kill();
    sender.join();
}
