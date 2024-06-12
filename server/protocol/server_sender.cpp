#include "./server_sender.h"

#include "../../common/common_liberror.h"

ServerSender::ServerSender(ServerProtocol& protocol):
        server_protocol(protocol), queue(std::make_shared<Queue<std::shared_ptr<Message>>>()) {}

bool ServerSender::is_dead() { return _keep_running; }

void ServerSender::stop() {
    _keep_running = false;
    queue->close();
}

void ServerSender::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> msg = queue->pop();
            server_protocol.send_message(msg);
        }
    } catch (const ClosedQueue& err) {
        _keep_running = false;
    } catch (const LibError& err) {
        if (_keep_running) {
            throw LibError(err);
        }
    }
}

std::shared_ptr<Queue<std::shared_ptr<Message>>>& ServerSender::get_sender_queue() { return queue; }

void ServerSender::change_sender_queue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& new_queue) {
    this->queue = new_queue;
}

ServerSender::~ServerSender() = default;
