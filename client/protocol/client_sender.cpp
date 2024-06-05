#include "./client_sender.h"

#include <iostream>

ClientSender::ClientSender(ClientProtocol& client_protocol, Queue<std::shared_ptr<Message>>& queue):
        client_protocol(client_protocol), queue(queue) {}

void ClientSender::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> msg = queue.pop();
            client_protocol.send_message(msg);
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    }
}

bool ClientSender::is_dead() { return _keep_running; }

void ClientSender::stop() {
    _keep_running = false;
    queue.close();
}

ClientSender::~ClientSender() {}
