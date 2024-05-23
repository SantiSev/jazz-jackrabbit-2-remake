#include <iostream>

#include "../common/common_socket.h"

#define servname argv[1]

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Expected format: ./server <port>\n";
            return EXIT_FAILURE;
        }

        Socket acceptor(servname);
        Socket client = acceptor.accept();

        uint8_t data;
        bool was_closed = false;
        client.recvall(&data, sizeof(data), &was_closed);

        std::cout << int(data) << std::endl;
    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
