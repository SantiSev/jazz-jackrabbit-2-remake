#include "./server_receiver.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<std::unique_ptr<Message>>& queue):
        server_protocol(protocol), queue(queue) {}

bool ServerReceiver::is_dead() { return _keep_running; }

void ServerReceiver::kill() { _keep_running = false; }

void ServerReceiver::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<Message> message = server_protocol.recv_message();
            queue.try_push(message);
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ServerReceiver::~ServerReceiver() {}
