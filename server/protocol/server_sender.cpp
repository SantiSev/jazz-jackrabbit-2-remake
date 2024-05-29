#include "./server_sender.h"

ServerSender::ServerSender(ServerProtocol& protocol,
                           std::shared_ptr<Queue<std::shared_ptr<Message>>>& queue):
        server_protocol(protocol), queue(queue) {}

bool ServerSender::is_dead() { return _keep_running; }

void ServerSender::kill() { _keep_running = false; }

void ServerSender::run() {
    try {
        // TODO: What type of data needs should be popped from the queue
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ServerSender::~ServerSender() {}

std::shared_ptr<Queue<std::shared_ptr<Message>>> ServerSender::get_sender_queue() { return queue; }

void ServerSender::change_sender_queue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& new_queue) {
    this->queue = new_queue;
}