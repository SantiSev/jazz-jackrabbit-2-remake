#include <iostream>

#include "./protocol/server_protocol.h"

#define servname argv[1]

int main(int argc, char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Expected format: ./server <port>\n";
            return EXIT_FAILURE;
        }

        Socket acceptor(servname);
        ServerProtocol protocol(acceptor.accept());

        while (!protocol.is_closed()) {
            std::shared_ptr<Message> msg = protocol.recv_message();
            if (protocol.is_closed())
                break;
            msg->run();
        }

    } catch (const std::exception& err) {
        std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
        return -1;
    } catch (...) {
        std::cerr << "Something went wrong and an unknown exception was caught.\n";
        return -1;
    }
}
