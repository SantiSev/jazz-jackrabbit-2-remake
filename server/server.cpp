#include "server.h"

#include <iostream>
#include <utility>

#include "game_logic/matches_manager.h"

#include "accepter.h"

void Server::run() {
    try {
        auto accepter = new ServerAccepter("8080");
        accepter->start();

        std::string serverInput;
        while (true) {
            std::cin >> serverInput;
            if (serverInput == "q") {
                break;
            }
        }

        accepter->stop();
        accepter->join();
        delete accepter;
    } catch (const std::exception& err) {
        std::cerr << "An exception was caught in server_class: " << err.what() << "\n";
    }
}

const std::string& Server::get_servname() { return portDir; }

Server::Server(std::string port): portDir(std::move(port)) {}

Server::~Server() = default;
