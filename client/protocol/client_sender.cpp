#include "./client_sender.h"

#include <iostream>

#include "../../common/common_liberror.h"

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
    } catch (const LibError& err) {
        if (_keep_running) {
            throw LibError(err);
        }
    }
}

bool ClientSender::is_dead() { return _keep_running; }

void ClientSender::stop() {
    _keep_running = false;
    queue.close();
}

ClientSender::~ClientSender() {}
