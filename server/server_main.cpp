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
        while (!was_closed) {
            client.recvall(&data, sizeof(data), &was_closed);
            if (was_closed)
                break;

            if (data == 0x00)
                std::cout << "CONNECTION_EVENT" << std::endl;
            else if (data == 0x01)
                std::cout << "IN_GAME_EVENT" << std::endl;
            else if (data == 0x02)
                std::cout << "MENU_EVENT" << std::endl;
        }

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
