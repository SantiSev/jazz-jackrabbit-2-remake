#include <iostream>

#include "../common/common_socket.h"

#define hostname argv[1]
#define servname argv[2]

int main(int argc, char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        Socket server(hostname, servname);

        std::string event;
        while (std::cin >> event) {
            uint8_t proof;
            bool was_closed = false;
            if (event.compare("CONNECTION_EVENT") == 0) {
                proof = 0x00;
                server.sendall(&proof, sizeof(proof), &was_closed);
            } else if (event.compare("IN_GAME_EVENT") == 0) {
                proof = 0x01;
                server.sendall(&proof, sizeof(proof), &was_closed);
            } else if (event.compare("MENU_EVENT") == 0) {
                proof = 0x02;
                server.sendall(&proof, sizeof(proof), &was_closed);
            }
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
