#include "test_client_server.h"

void TestClientServer::change_receiver_queue(
        std::shared_ptr<Queue<std::shared_ptr<Message>>>& eventQueue) {}


void TestClientServer::change_sender_queue(std::shared_ptr<Queue<Snapshot>>& snapshotQueue) {}

void TestClientServer::start() {
    // todo receiver start
    // todo sender start
}

std::shared_ptr<Queue<std::shared_ptr<Message>>> TestClientServer::get_receiver_queue() {
    return event_queue;
}

std::shared_ptr<Queue<Snapshot>> TestClientServer::get_sender_queue() { return snapshot_queue; }
