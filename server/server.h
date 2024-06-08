#ifndef TP_FINAL_SERVER_H
#define TP_FINAL_SERVER_H

#include <iostream>
#include <string>
#include <utility>

#include "game_logic/matches_manager.h"
#include "protocol/accepter.h"

#define QUIT "q"

class Server {
private:
    ServerAccepter* accepter;

public:
    // Constructor of the Server class, initializes the protocol and receives the port as a
    // parameter to create the socket
    explicit Server(const std::string& port);

    // cant copy or move
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(Server&&) = delete;

    // Run the server, creates and throws two threads, the accepter and the gameloop (logic of the
    // game), then waits for the user to close the server
    void run();

    // Destroyer
    ~Server();
};

#endif
