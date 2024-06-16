#include "client_message_handler.h"

#include "../client.h"

ClientMessageHandler::ClientMessageHandler(Client& client): client(client) {}

void ClientMessageHandler::send_command(command_t command) {
    CommandDTO dto{client.id_client, command};
    send_message.push(std::make_shared<RecvCommandMessage>(dto));
#ifdef LOG_VERBOSE
    std::cout << "Sending command: " << int(command) << std::endl;
#endif
}

void ClientMessageHandler::create_match(character_t character, map_list_t map_name,
                                        uint8_t max_players) {
    CreateGameDTO dto = {client.id_client, character, map_name, max_players};
    send_message.push(std::make_shared<RecvCreateGameMessage>(dto));
#ifdef LOG
    std::cout << "Creating match" << std::endl;
#endif
}

void ClientMessageHandler::join_match(id_match_t id_match, character_t character) {
    JoinMatchDTO dto = {client.id_client, id_match, character};
    send_message.push(std::make_shared<RecvJoinMatchMessage>(dto));
#ifdef LOG
    std::cout << "Joining match" << std::endl;
#endif
}

void ClientMessageHandler::quit() {
    CloseConnectionDTO dto{client.id_client};
    send_message.push(std::make_shared<CloseConnectionMessage>(dto));
#ifdef LOG
    std::cout << "Quitting" << std::endl;
#endif
}

void ClientMessageHandler::handle_acpt_connection(const id_client_t& client_id) {
    client.id_client.store(client_id);
#ifdef LOG
    std::cout << "Connected to server with id: " << client_id << std::endl;
#endif
}

void ClientMessageHandler::handle_recv_close_connection(const CloseConnectionDTO& dto) {
    client.menu_running.store(false);
    client.match_running.store(false);
    client.game_running.store(false);
#ifdef LOG
    std::cout << "Connection closed by server" << std::endl;
#endif
}

void ClientMessageHandler::handle_connected_to_match(const ClientHasConnectedToMatchDTO& dto) {
    client.map_enum.store(dto.map);
    client.menu_running.store(false);
    client.match_running.store(true);
#ifdef LOG
    std::cout << "Connected to match" << std::endl;
#endif
}

void ClientMessageHandler::handle_recv_active_games(const MatchInfoDTO& dto) {
    // TODO set menu active games list
    // send_message.push(std::make_shared<RecvActiveGames>(dto));
#ifdef LOG
    std::cout << "Received active games" << std::endl;
#endif
}

void ClientMessageHandler::handle_recv_finish_match() {
    client.menu_running.store(true);
    client.match_running.store(false);
#ifdef LOG
    std::cout << "Match Finished" << std::endl;
#endif
}

void ClientMessageHandler::handle_recv_game_state(const GameStateDTO& dto) {
    game_state_q.push(std::make_shared<GameStateDTO>(dto));
#ifdef LOG_VERBOSE
    std::cout << "Received game state" << std::endl;
#endif
}
