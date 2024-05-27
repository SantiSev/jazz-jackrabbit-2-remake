#include "server.h"

#include <iostream>
#include <utility>

#include "game_logic/matches_manager.h"

void Server::run() {
    try {
        auto matches_manager = new MatchesManager();
        matches_manager->start();

        std::string serverInput;
        while (true) {
            std::cin >> serverInput;
            if (serverInput == "q") {
                break;
            }
        }

        matches_manager->stop();
        matches_manager->join();
        delete matches_manager;
    } catch (const std::exception& err) {
        std::cerr << "An exception was caught in server_class: " << err.what() << "\n";
    }
}

const std::string& Server::get_servname() { return portDir; }

Server::Server(std::string port): portDir(std::move(port)) {}

Server::~Server() = default;
