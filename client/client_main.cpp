#include <iostream>
#include <memory>

#include <arpa/inet.h>

#include "../common/common_socket.h"
#include "../common/protocol/messages/menu_events/recv_create_game.h"
#include "../common/protocol/messages/menu_events/send_game_created.h"

#define hostname argv[1]
#define servname argv[2]
#define QUIT 'q'

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        Socket server(hostname, servname);

        uint16_t event;
        auto create_meesage = std::make_shared<RecvCreateGameMessage>();
        while (std::cin.get() != QUIT) {
            bool was_closed = false;
            if (std::cin.get() == 'c') {}
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
