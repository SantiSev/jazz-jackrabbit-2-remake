#include <iostream>
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
                protocol.send_finish_match();
            } else if (command.compare(GAME_STATE) == 0) {
                protocol.send_game_state();
            } else if (command.compare(ACTIVE_GAMES) == 0) {
                int length;
                std::cin >> length;
                std::vector<Match> matches;

                for (int i = 0; i < length; i++) {
                    std::string name;
                    int players;

                    std::cin >> name;
                    std::cin >> players;

                    matches.push_back({name, uint8_t(players)});
                }


                protocol.send_active_games(length, matches);
            } else if (command.compare(GAME_CREATED) == 0) {
                protocol.send_game_created();
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
