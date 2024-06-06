#include <iostream>
#include <memory>

#include <arpa/inet.h>

#include "../common/common_socket.h"
#include "protocol/client_thread_manager.h"

#define hostname argv[1]
#define servname argv[2]
#define QUIT 'q'

// #include <SDL2pp/SDL2pp.hh>
//
//  using namespace SDL2pp;

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        std::string line;
        ClientProtocol protocol(hostname, servname);
        std::getline(std::cin, line);
        if (line == "c") {
            //            CreateGameDTO dto = {1, static_cast<character_t>(0), 2, 2};// 2 jugadores,
            //            conecte este primero
            CreateGameDTO dto = {1, static_cast<character_t>(1), 2, 1};  // 1 jugador, solo este
            auto message = std::make_shared<RecvCreateGameMessage>(dto);
            protocol.send_message(message);
        }
        if (line == "j") {
            JoinMatchDTO dto = {2, 1, static_cast<character_t>(0)};
            auto message = std::make_shared<RecvJoinMatchMessage>(dto);
            protocol.send_message(message);
        }
        //         protocol.send_create_game(1, message, 7);
        //         protocol.send_join_match(4, 7, 12);
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
