#include "server.h"

#include <iostream>

#include "server_eventloop.h"
#include "server_gameloop.h"

void Server::run() {
    try {
        Queue<std::string> event_queue;
        Queue<std::string> command_queue;
        auto gameloop = new Server_Gameloop(event_queue);
        auto eventloop = new Server_Eventloop(event_queue, command_queue);
        gameloop->start();
        eventloop->start();


        std::string serverInput;
        while (true) {
            std::cin >> serverInput;
            if (serverInput == "q") {
                break;
            }
        }

        eventloop->stop();
        eventloop->join();
        gameloop->stop();
        gameloop->join();
        delete gameloop;
        delete eventloop;
    } catch (const std::exception& err) {
        std::cerr << "An exception was caught in server_class: " << err.what() << "\n";
    }
}

const std::string& Server::get_servname() { return portDir; }


Server::Server(const std::string& port): portDir(port) {}

Server::~Server() {}
