#include "server.h"

#include <iostream>
#include <utility>

#include "server_eventloop.h"
#include "server_gameloop.h"

void Server::run() {
    try {
        Queue<Message> event_queue;
        Queue<Snapshot> snapshot_queue;
        auto gameloop = new Server_Gameloop(event_queue, snapshot_queue);
        gameloop->start();


        std::string serverInput;
        while (true) {
            std::cin >> serverInput;
            if (serverInput == "q") {
                break;
            }
        }

        gameloop->stop();
        gameloop->join();
        delete gameloop;
    } catch (const std::exception& err) {
        std::cerr << "An exception was caught in server_class: " << err.what() << "\n";
    }
}

const std::string& Server::get_servname() { return portDir; }

Server::Server(std::string port): portDir(std::move(port)) {}

Server::~Server() = default;
