#ifndef TP_FINAL_CLIENT_MONITOR_H
#define TP_FINAL_CLIENT_MONITOR_H

#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>

#include "../../common/common_queue.h"
#include "../../common/protocol/messages/common_message.h"

class ClientMonitor {
private:
    std::list<std::reference_wrapper<Queue<std::shared_ptr<Message>>>> clientQueues;
    std::mutex mutex;
    int match_id = 0;

public:
    // Constructor
    ClientMonitor();
    // Add a client to the list of clients (Thread safe)
    void addClient(Queue<std::shared_ptr<Message>>& queue);
    // Broadcast message to all clients (Thread safe), pushing (Blocking) the message to the queue
    // of each client
    void broadcastClients(const std::shared_ptr<Message>& gameMessage);
    //    void removeQueue(std::shared_ptr<Queue<std::shared_ptr<Message>>> queueToRemove);
    void removeQueue(const Queue<std::shared_ptr<Message>>& queueToRemove);

    ClientMonitor(const ClientMonitor&) = delete;
    ClientMonitor& operator=(const ClientMonitor&) = delete;
    // Destroyer
    ~ClientMonitor() = default;

    void remove_all_queues();

    int get_match_id() const;
};
#endif
