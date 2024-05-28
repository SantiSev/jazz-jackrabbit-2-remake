#include "./server_sender.h"

ServerSender::ServerSender(ServerProtocol& protocol, Queue<int>& queue):
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
