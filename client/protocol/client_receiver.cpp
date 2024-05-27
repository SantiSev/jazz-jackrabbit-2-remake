#include "./client_receiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& client_protocol,
                               Queue<std::unique_ptr<Message>>& queue):
        client_protocol(client_protocol), queue(queue) {}

void ClientReceiver::run() {
    try {
        while (_keep_running) {
            std::unique_ptr<Message> message = client_protocol.recv_message();
            queue.try_push(message);
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ClientReceiver::~ClientReceiver() {}
