#ifndef TP_FINAL_ACCEPTER_H
#define TP_FINAL_ACCEPTER_H

#include <list>
#include <string>
#include <utility>
#include <vector>

#include "../game_logic/matches_manager.h"

class ServerAccepter: public Thread {
private:
    Socket skt;
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
