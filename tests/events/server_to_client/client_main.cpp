#include <iostream>

#include <arpa/inet.h>

#include "../../../client/protocol/client_protocol.h"

#define hostname argv[1]
#define servname argv[2]

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        ClientProtocol protocol(hostname, servname);

        std::string command;
        while (std::cin >> command) {
            if (command.compare("q") == 0)
                break;
        }
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
    return 0;
}
