#include "./client_receiver.h"

#include "../../common/common_liberror.h"

ClientReceiver::ClientReceiver(ClientProtocol& client_protocol,
                               Queue<std::shared_ptr<Message>>& queue):
        client_protocol(client_protocol), queue(queue) {}

bool ClientReceiver::is_dead() { return _keep_running; }

void ClientReceiver::stop() {
    _keep_running = false;
    queue.close();
}

void ClientReceiver::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> message = client_protocol.recv_message();
            _keep_running = !client_protocol.is_closed();
            if (_keep_running) {
                queue.push(message);
            }
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    } catch (const LibError& err) {
        if (_keep_running) {
            throw LibError(err);
        }
    }
}

ClientReceiver::~ClientReceiver() = default;
