#include "./server_sender.h"

ServerSender::ServerSender(ServerProtocol& protocol, Queue<int>& queue):
        server_protocol(protocol), queue(queue) {}

void ServerSender::run() {
    try {
        // TODO: What type of data needs should be popped from the queue
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ServerSender::~ServerSender() {}
