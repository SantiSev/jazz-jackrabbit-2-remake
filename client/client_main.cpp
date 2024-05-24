#include <iostream>

#include <arpa/inet.h>

#include "../common/common_socket.h"

#define hostname argv[1]
#define servname argv[2]

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        Socket server(hostname, servname);

        uint16_t event;
        while (std::cin >> event) {
            bool was_closed = false;
            event = htons(event);
            server.sendall(&event, sizeof(event), &was_closed);
            if (was_closed)
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
