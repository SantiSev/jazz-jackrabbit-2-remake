#include <iostream>

#include <arpa/inet.h>

#include "../../../client/protocol/client_protocol.h"

#define hostname argv[1]
#define servname argv[2]

#define CHEAT_COMMAND "CHEAT_COMMAND"
#define COMMAND "COMMAND"
#define CREATE_GAME "CREATE_GAME"
#define JOIN_MATCH "JOIN_MATCH"
#define LEAVE_MATCH "LEAVE_MATCH"

int main(int argc, const char* argv[]) {
    try {
        if (argc != 3) {
            std::cerr << "Expected format: ./client <hostname> <port>\n";
        }

        ClientProtocol protocol(hostname, servname);

        std::string command;
        while (std::cin >> command) {
            if (command.compare("q") == 0)
                break;

            if (command.compare(CHEAT_COMMAND) == 0) {
                int id_player;
                int id_cheat_command;

                std::cin >> id_player;
                std::cin >> id_cheat_command;

                protocol.send_cheat_command(id_player, id_cheat_command);
            } else if (command.compare(COMMAND) == 0) {
                int id_player;
                int id_command;

                std::cin >> id_player;
                std::cin >> id_command;

                protocol.send_command(id_player, id_command);
            } else if (command.compare(CREATE_GAME) == 0) {
                int id_player;
                std::string match_name;

                std::cin >> id_player;
                std::cin >> match_name;

                protocol.send_create_game(id_player, match_name);
            } else if (command.compare(JOIN_MATCH) == 0) {
                int id_player;
                int id_match;
                int player_character;

                std::cin >> id_player;
                std::cin >> id_match;
                std::cin >> player_character;

                protocol.send_join_match(id_player, id_match, player_character);
            } else if (command.compare(LEAVE_MATCH) == 0) {
                int id_player;

                std::cin >> id_player;

                protocol.send_leave_match(id_player);
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
