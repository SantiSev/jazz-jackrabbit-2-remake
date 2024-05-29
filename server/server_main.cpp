#include <iostream>

#include "server.h"

int main(int argc, const char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Expected format: ./server <port>\n";
            return EXIT_FAILURE;
        }

        Server server(servname);
        server.run();

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
