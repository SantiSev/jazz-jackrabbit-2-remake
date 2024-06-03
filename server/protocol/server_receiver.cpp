#include "./server_receiver.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol,
                               std::shared_ptr<Queue<std::shared_ptr<Message>>>& queue):
        server_protocol(protocol), queue(queue) {}

bool ServerReceiver::is_dead() { return _keep_running; }

void ServerReceiver::kill() { _keep_running = false; }

void ServerReceiver::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> message = server_protocol.recv_message();
            if (_keep_running) {
                queue->push(message);
            }
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ServerReceiver::~ServerReceiver() {}

std::shared_ptr<Queue<std::shared_ptr<Message>>>& ServerReceiver::get_receiver_queue() {
    return queue;
}

void ServerReceiver::change_receiver_queue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& sharedPtr) {
    queue = sharedPtr;
}
