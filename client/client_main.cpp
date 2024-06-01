#include <iostream>
#include <memory>

#include <arpa/inet.h>

#include "../common/common_socket.h"
#include "../common/protocol/messages/menu_events/recv_create_game.h"
#include "../common/protocol/messages/menu_events/send_game_created.h"
#include "protocol/client_thread_manager.h"

#define hostname argv[1]
#define servname argv[2]
#define QUIT 'q'

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        ClientProtocol protocol(hostname, servname);
        std::string message = "match 1";
        protocol.send_create_game(1, message, 7);
        //        protocol.send_join_match(4, 7, 12);
        //        uint16_t event;
        //        bool was_closed = false;

        while (std::cin.get() != QUIT) {
            //            was_closed = false;
            //            event = htons(event);
            //            server.sendall(&event, sizeof(event), &was_closed);
            //            if (was_closed)
            //                break;
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
