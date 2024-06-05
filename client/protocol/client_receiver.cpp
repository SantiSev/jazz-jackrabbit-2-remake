#include "./client_receiver.h"

ClientReceiver::ClientReceiver(ClientProtocol& client_protocol,
                               Queue<std::shared_ptr<Message>>& queue):
        client_protocol(client_protocol), queue(queue) {}

bool ClientReceiver::is_dead() { return _keep_running; }

void ClientReceiver::kill() { _keep_running = false; }

void ClientReceiver::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> message = client_protocol.recv_message();
            queue.try_push(message);
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

ClientReceiver::~ClientReceiver() = default;
