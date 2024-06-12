#include "server.h"

Server::Server(const std::string& port): accepter(new ServerAccepter(port)) {}

void Server::run() {
    try {
        accepter->start();

        std::string serverInput;
        while (true) {
            std::cin >> serverInput;
            if (serverInput == QUIT) {
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

Server::~Server() = default;
