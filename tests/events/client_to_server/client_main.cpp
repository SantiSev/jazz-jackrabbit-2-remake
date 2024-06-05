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

// int main(int argc, const char* argv[]) {
//     try {
//         if (argc != 3) {
//             std::cerr << "Expected format: ./client <hostname> <port>\n";
//         }
//
//         ClientProtocol protocol(hostname, servname);
//
//         std::string command;
//         while (std::cin >> command) {
//             if (command.compare("q") == 0)
//                 break;
//
//             if (command.compare(CHEAT_COMMAND) == 0) {
//                 id_player_t id_player;
//                 std::cin >> id_player;
//                 cheat_command_t cheat_command = INFINITY_AMMO;
//
//                 CheatCommandDTO cheat_command_dto = {id_player, cheat_command};
//                 auto message = std::make_shared<RecvCheatCommandMessage>(cheat_command_dto);
//                 protocol.send_message(message);
//             } else if (command.compare(COMMAND) == 0) {
//                 id_player_t id_player;
//                 std::cin >> id_player;
//                 command_t command = MOVE_LEFT;
//
//                 CommandDTO command_dto = {id_player, command};
//                 auto message = std::make_shared<RecvCommandMessage>(command_dto);
//                 protocol.send_message(message);
//             } else if (command.compare(CREATE_GAME) == 0) {
//                 id_player_t id_player;
//                 std::cin >> id_player;
//
//                 CreateGameDTO create_game = {id_player, "Partida 1"};
//                 auto message = std::make_shared<RecvCreateGameMessage>(create_game);
//                 protocol.send_message(message);
//             } else if (command.compare(JOIN_MATCH) == 0) {
//                 id_player_t id_player;
//                 std::cin >> id_player;
//                 id_match_t id_match;
//                 std::cin >> id_match;
//
//                 JoinMatchDTO join_match = {id_player, id_match, JAZZ_CHARACTER};
//                 auto message = std::make_shared<RecvJoinMatchMessage>(join_match);
//                 protocol.send_message(message);
//             } else if (command.compare(LEAVE_MATCH) == 0) {
//                 id_player_t id_player;
//                 std::cin >> id_player;
//
//                 LeaveMatchDTO leave_match = {id_player};
//                 auto message = std::make_shared<RecvLeaveMatchMessage>(leave_match);
//                 protocol.send_message(message);
//             }
//         }
//     } catch (const std::exception& err) {
//         std::cerr << "Something went wrong and an exception was caught: " << err.what() << "\n";
//         return -1;
//     } catch (...) {
//         std::cerr << "Something went wrong and an unknown exception was caught.\n";
//         return -1;
//     }
//     return 0;
// }
