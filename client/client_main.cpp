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

        uint8_t proof = 0x01;
        bool was_closed = false;
        server.sendall(&proof, sizeof(proof), &was_closed);
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
    return 0;
}
