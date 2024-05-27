#include "client_monitor.h"

#include <algorithm>


ClientMonitor::ClientMonitor(): clientQueues() {}

void ClientMonitor::addClient(Queue<std::shared_ptr<Message>> queue) {
    std::unique_lock<std::mutex> lck(mutex);
    clientQueues.emplace_back(queue);
}

void ClientMonitor::broadcastClients(const std::shared_ptr<Message>& gameMessage) {
    std::unique_lock<std::mutex> lck(mutex);
    auto queue = clientQueues.begin();
    while (queue != clientQueues.end()) {
        Queue<std::shared_ptr<Message>>& returnQueue = queue->get();
        try {
            returnQueue.push(gameMessage);
            ++queue;
        } catch (const std::exception& err) {
            queue = clientQueues.erase(queue);
        }
    }
}

void ClientMonitor::removeQueue(Queue<std::shared_ptr<Message>> const queueToRemove) {
    std::lock_guard<std::mutex> lock(mutex);
    auto queue = std::find_if(clientQueues.begin(), clientQueues.end(),
                              [&](const auto& ref) { return &(ref.get()) == &queueToRemove; });
    if (queue != clientQueues.end()) {
        clientQueues.erase(queue);
    }
}
