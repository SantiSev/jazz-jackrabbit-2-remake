#include "./client_sender.h"

ClientSender::ClientSender(ClientProtocol& client_protocol, Queue<std::shared_ptr<Message>>& queue):
        client_protocol(client_protocol), queue(queue) {}

bool ClientSender::is_dead() { return _keep_running; }

void ClientSender::kill() { _keep_running = false; }

void ClientSender::run() {
    try {
        // TODO: What type of data needs should be popped from the queue
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ClientSender::~ClientSender() {}
