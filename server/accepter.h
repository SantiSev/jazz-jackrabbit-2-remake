#ifndef TP_FINAL_ACCEPTER_H
#define TP_FINAL_ACCEPTER_H

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "../common/common_queue.h"
#include "../common/common_socket.h"
#include "../common/common_thread.h"
#include "game_logic/client_monitor.h"
#include "game_logic/matches_manager.h"

#include "test_client_server.h"


class ServerAccepter: public Thread {
private:
    Socket skt;
    std::atomic<bool> online{true};
    MatchesManager matches_manager;

public:
    // Constructor of the ServerAccepter class
    explicit ServerAccepter(const std::string& port);
    void run() override;
    // Kills the running thread
    void stop() override;
    // Destroyer
    ~ServerAccepter() override = default;
};

#endif
