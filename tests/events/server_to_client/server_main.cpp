#include <iostream>
#include <memory>
#include <vector>

#include <arpa/inet.h>

#include "../../../server/protocol/server_protocol.h"

#define servname argv[1]

#define FINISH_MATCH "FINISH_MATCH"
#define GAME_STATE "GAME_STATE"
#define ACTIVE_GAMES "ACTIVE_GAMES"
#define GAME_CREATED "GAME_CREATED"

int main(int argc, const char* argv[]) {
    try {
        if (argc != 2) {
            std::cerr << "Expected format: ./server <port>\n";
            return EXIT_FAILURE;
        }

        Socket acceptor(servname);
        ServerProtocol protocol(acceptor.accept());

        std::string command;
        while (std::cin >> command) {
            if (command.compare("q") == 0)
                break;

            if (command.compare(FINISH_MATCH) == 0) {
                FinishMatchDTO finish_match_dto = {};
                auto message = std::make_shared<SendFinishMatchMessage>(finish_match_dto);
                protocol.send_message(message);
            } else if (command.compare(GAME_STATE) == 0) {
                GameStateDTO game_state_dto = {};
                auto message = std::make_shared<SendGameStateMessage>(game_state_dto);
                protocol.send_message(message);
            } else if (command.compare(ACTIVE_GAMES) == 0) {
                ActiveGamesDTO active_game_dto = {"Partida 1", 5};
                auto message = std::make_shared<SendActiveGamesMessage>(active_game_dto);
                protocol.send_message(message);
            } else if (command.compare(GAME_CREATED) == 0) {
                GameCreatedDTO game_created_dto = {};
                auto message = std::make_shared<SendGameCreatedMessage>(game_created_dto);
                protocol.send_message(message);
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
