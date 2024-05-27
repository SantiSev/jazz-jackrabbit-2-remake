#ifndef TP_FINAL_CLIENT_MONITOR_H
#define TP_FINAL_CLIENT_MONITOR_H

#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>

#include "../../common/common_queue.h"
#include "../../common/message/message.h"

#include "snapshot.h"


class ClientMonitor {
private:
    std::list<std::reference_wrapper<std::shared_ptr<Queue<Snapshot>>>> clientQueues;
    std::mutex mutex;

public:
    // Constructor
    ClientMonitor();
    // Add a client to the list of clients (Thread safe)
    void addClient(std::shared_ptr<Queue<Snapshot>> queue);
    // Broadcast message to all clients (Thread safe), pushing (Blocking) the message to the queue
    // of each client
    void broadcastClients(const Snapshot& gameMessage);
    void removeQueue(std::shared_ptr<Queue<Snapshot>> queueToRemove);

    ClientMonitor(const ClientMonitor&) = delete;
    ClientMonitor& operator=(const ClientMonitor&) = delete;
    // Destroyer
    ~ClientMonitor() = default;
};
#endif
