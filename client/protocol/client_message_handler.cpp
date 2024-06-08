#include "client_message_handler.h"

#include "../client.h"

ClientMessageHandler::ClientMessageHandler(Client& client): client(client) {}

void ClientMessageHandler::send_command(command_t command) {
    CommandDTO dto{client.id_player, command};
    send_message.push(std::make_shared<RecvCommandMessage>(dto));
}

void ClientMessageHandler::create_match(character_t character, map_list_t map_name,
                                        uint8_t max_players) {
    CreateGameDTO dto = {};
    dto.id_client = client.id_client;
    dto.character_selected = character;
    dto.map_name = map_name;
    dto.max_players = max_players;
    send_message.push(std::make_shared<RecvCreateGameMessage>(dto));
}

void ClientMessageHandler::join_match(id_match_t id_match, character_t character) {
    JoinMatchDTO dto = {};
    dto.id_client = client.id_client;
    dto.id_match = id_match;
    dto.player_character = character;
    send_message.push(std::make_shared<RecvJoinMatchMessage>(dto));
}

void ClientMessageHandler::quit() {
    CloseConnectionDTO dto{client.id_client};
    send_message.push(std::make_shared<CloseConnectionMessage>(dto));
}

void ClientMessageHandler::handle_acpt_connection(const id_client_t& client_id) {
    client.id_client.store(client_id);
}

void ClientMessageHandler::handle_recv_close_connection(const CloseConnectionDTO& dto) {
    client.close();
}

void ClientMessageHandler::handle_connected_to_match(const ClientHasConnectedToMatchDTO& dto) {
    send_message.push(std::make_shared<SendConnectedToGameMessage>(dto));
}

void ClientMessageHandler::handle_recv_active_games(const MatchInfoDTO& dto) {
    // TODO set menu active games list
    // send_message.push(std::make_shared<RecvActiveGames>(dto));
}

void ClientMessageHandler::handle_recv_game_state(const GameStateDTO& dto) {
    game_state_q.push(std::make_shared<GameStateDTO>(dto));
}
