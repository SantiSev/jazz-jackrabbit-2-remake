#ifndef TP_FINAL_TEST_CLIENT_SERVER_H
#define TP_FINAL_TEST_CLIENT_SERVER_H

#include <algorithm>
#include <memory>
#include <utility>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/message/message.h"
#include "game_logic/snapshot.h"

class TestClientServer {
private:
    Socket skt;
    std::shared_ptr<Queue<std::shared_ptr<Message>>>& event_queue;
    std::shared_ptr<Queue<Snapshot>> snapshot_queue;

public:
    explicit TestClientServer(Socket skt,
                              std::shared_ptr<Queue<std::shared_ptr<Message>>>& eventQueue):
            skt(std::move(skt)), event_queue(eventQueue) {}

    ~TestClientServer() = default;

    void change_receiver_queue(std::shared_ptr<Queue<std::shared_ptr<Message>>>& eventQueue);

    void change_sender_queue(std::shared_ptr<Queue<Snapshot>>& snapshotQueue);

    std::shared_ptr<Queue<std::shared_ptr<Message>>> get_receiver_queue();

    std::shared_ptr<Queue<Snapshot>> get_sender_queue();

    void start();
};


#endif
