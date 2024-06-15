#include "client_monitor.h"

#include <algorithm>
#include <iostream>


ClientMonitor::ClientMonitor(): clientQueues() {}

void ClientMonitor::addClient(std::shared_ptr<Queue<std::shared_ptr<Message>>>& queue) {
    std::unique_lock<std::mutex> lck(mutex);
    clientQueues.emplace_back(queue);
}

void ClientMonitor::broadcastClients(const std::shared_ptr<Message>& gameMessage) {
    std::unique_lock<std::mutex> lck(mutex);
    auto queue = clientQueues.begin();
    while (queue != clientQueues.end()) {
        std::shared_ptr<Queue<std::shared_ptr<Message>>>& returnQueue = queue->get();
        try {
            returnQueue->push(gameMessage);
            ++queue;
        } catch (const std::exception& err) {
            queue = clientQueues.erase(queue);
        }
    }
}

void ClientMonitor::removeQueue(
        const std::shared_ptr<Queue<std::shared_ptr<Message>>>& queueToRemove) {
    for (auto it = clientQueues.begin(); it != clientQueues.end();) {
        if (it->get() == queueToRemove) {
            it = clientQueues.erase(it);
        } else {
            ++it;
        }
    }
}

void ClientMonitor::remove_all_queues() {
    std::lock_guard<std::mutex> lock(mutex);
    clientQueues.clear();
}

int ClientMonitor::get_match_id() const { return match_id; }
