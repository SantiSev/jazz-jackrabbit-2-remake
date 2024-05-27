#include "./client_sender.h"

ClientSender::ClientSender(ClientProtocol& client_protocol, Queue<int>& queue):
        client_protocol(client_protocol), queue(queue) {}

void ClientSender::run() {
    try {
        // TODO: What type of data needs should be popped from the queue
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ClientSender::~ClientSender() {}
