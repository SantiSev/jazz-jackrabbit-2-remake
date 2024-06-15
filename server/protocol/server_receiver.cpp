#include "./server_receiver.h"

#include "../../common/common_liberror.h"

ServerReceiver::ServerReceiver(ServerProtocol& protocol, Queue<std::shared_ptr<Message>>& queue):
        server_protocol(protocol), queue(queue) {}

bool ServerReceiver::is_dead() { return _keep_running; }

void ServerReceiver::stop() {
    _keep_running = false;
    //    queue->close();
}

void ServerReceiver::run() {
    try {
        while (_keep_running) {
            std::shared_ptr<Message> message = server_protocol.recv_message();
            _keep_running = !server_protocol.is_closed();
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

ServerReceiver::~ServerReceiver() {}

// std::shared_ptr<Queue<std::shared_ptr<Message>>>& ServerReceiver::get_receiver_queue() {
//     return queue;
// }
//
// void ServerReceiver::change_receiver_queue(
//         const std::shared_ptr<Queue<std::shared_ptr<Message>>>& sharedPtr) {
//     queue = sharedPtr;
// }

bool ServerReceiver::isAlive() { return _keep_running; }
