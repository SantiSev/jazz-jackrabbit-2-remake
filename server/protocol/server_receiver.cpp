#include "./server_receiver.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<std::unique_ptr<Message>>& queue):
        server_protocol(protocol), queue(queue) {}

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
